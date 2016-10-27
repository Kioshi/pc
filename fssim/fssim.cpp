#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable: 4996) // _CRT_SECURE_NO_WARNINGS
#define nullptr 0
struct Node;
struct Childs
{
    int size;
    Node** arr;
};

struct Node
{
    char name[256];
    Node* parent;
    Childs* childs;
};

struct Array
{
    int size;
    char** string;
};

Node* root;
Node * current;


void print(Node * node, bool last = true)
{
    if (node->parent != node)
        print(node->parent, false);
    printf("%s", node->name);

    if (last)
        printf("\n");
}


void errNoArgs()
{
    printf("ERROR not enough arguments\n");
}
void errNoPath()
{
    printf("ERROR path does not exist\n");
}
void errNotDir()
{
    printf("ERROR target is not a directory\n");
}
void errNoSrcFile()
{
    printf("ERROR source file not found\n");
}
void errSrcDir()
{
    printf("ERROR source is directory\n");
}

Array* createArray()
{
    Array* arr = (Array*)malloc(sizeof(Array));
    arr->size = 0;
    arr->string = nullptr;
    return arr;
}

void push_back(Array* words, char* s)
{
    char** tmp = (char**)calloc(words->size+1, sizeof(char*));
    if (words->string)
    {
        for (int i = 0; i < words->size; i++)
            tmp[i] = words->string[i];
        //memcpy(tmp, words->string, sizeof(char*)*(words->size));
        free(words->string);
        words->string = nullptr;
    }
    words->string = tmp;
    char*string = (char*)calloc((strlen(s)+1), sizeof(char));
    strcpy(string, s);
    words->string[words->size++] = string;
}

Array* toArray(char* string)
{
    char s[256];
    int curr = 0;
    memset(s, 0, sizeof(s));
    Array* words = createArray();
    for (int i = 0; i < (int)strlen(string); i++)
    {
        if (curr == 256)
        {
            memset(s, 0, sizeof(s));
            curr = 0;
        }

        s[curr++] = string[i];
        if (string[i] == '/')
        {
            if (curr != 1)
                push_back(words,s);
            memset(s, 0, sizeof(s));
            curr = 0;
        }
    }
    if (strlen(s))
        push_back(words,s);

    return words;
}

Childs* createChilds()
{
    Childs* childs = (Childs*)malloc(sizeof(Childs));
    childs->size = 0;
    childs->arr = nullptr;
    return childs;
}

Node * createNode(char name[256], Node* parent = nullptr)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->parent = parent ? parent : node;
    memset(node->name, 0, 256);
    strcpy(node->name, name);
    node->childs = createChilds();
    return node;
}

void removeNode(Node* curr)
{
    if (!curr)
        return;

    for (int i = 0; i < curr->childs->size; i++)
        removeNode(curr->childs->arr[i]);

    free(curr->childs->arr);
    free(curr->childs);
    free(curr);
}

void pop_front(Array* words)
{
    if (words->size == 0)
        return;

    free(words->string[0]);
    words->string[0] = nullptr;
    if (--words->size)
    {
        for (int i = 1; i < words->size+1; i++)
            words->string[i - 1] = words->string[i];
    }
    else
    {
        free(words->string);
        words->string = nullptr;
    }
}

void addChild(Childs* childs, Node * node)
{
    Node** tmp = (Node**)calloc(childs->size+1, sizeof(Node*));
    if (childs->size > 0)
    {
        for (int i = 0; i < childs->size; i++)
            tmp[i] = childs->arr[i];
        free(childs->arr);
        childs->arr = nullptr;
    }
    childs->arr = tmp;
    childs->arr[childs->size++] = node;
}

void removeChild(Childs* childs, int index)
{
    for (int i = index + 1; i < childs->size; i++)
        childs->arr[i - 1] = childs->arr[i];

    if (--childs->size == 0)
    {
        free(childs->arr);
        childs->arr = nullptr;
    }
}

void insert(Node* curr,Array* words)
{
    if (!words->size)
        return;
    
    for (int i = 0; i < curr->childs->size; i++)
    {
        Node* c = curr->childs->arr[i];
        if (strcmp(c->name, words->string[0]) == 0)
        {
            pop_front(words);
            insert(c,words);
            return;
        }
    }
    Node* n = createNode(words->string[0], curr);
    addChild(curr->childs,n);
    pop_front(words);
    insert(n,words);
}

void deleteWords(Array* words)
{
    if (!words)
        return;

    for (int i = 0; i < words->size; i++)
        free(words->string[i]);
    if (words->string)
        free(words->string);
    free(words);
}

char * append(char* string, char c)
{
    if (!string)
        string = (char*)calloc(2, sizeof(char));
    else
    {
        char* tmp = (char*)calloc(strlen(string) + 2, sizeof(char));
        memcpy(tmp, string, strlen(string));
        free(string);
        string = tmp;
    }
    string[strlen(string)] = c;
    return string;
}

char * clear(char* string)
{
    if (string)
        free(string);
    return nullptr;
}


void processFilesystem(char* line)
{
    Array* words = toArray(line);
    if (words->size && strcmp(words->string[0], "/") == 0)
        pop_front(words);

    insert(root, words);
    deleteWords(words);
}

bool isDir(Node * node)
{
    return node->name[strlen(node->name) - 1] == '/';
}

Node * findNode(Node * curr, Array* words, bool onlyDir = true)
{
    if (!words->size)
        return curr;

    if (onlyDir && !isDir(curr))
        return curr;

    char* currString = (char*)calloc(strlen(words->string[0])+1,sizeof(char));
    strcpy(currString, words->string[0]);
    pop_front(words);
    while (strcmp(currString,"./") == 0 || strcmp(currString, ".") == 0)
    {
        if (!words->size)
        {
            free(currString);
            return curr;
        }

        currString = words->string[0];
        pop_front(words);
    }

    if (strcmp(currString, "../") == 0 || strcmp(currString, "..") == 0)
    {
        free(currString);
        return findNode(curr->parent, words, onlyDir);
    }

    for(int i = 0; i < curr->childs->size; i++)
    {
        Node* c = curr->childs->arr[i];
        if (strcmp(c->name, currString) == 0)
        {
            free(currString);
            return findNode(c, words, onlyDir);
        }
    }

    free(currString);
    return nullptr;
}

Node* getNode(char* path, bool onlyDir = true, bool currenWhenNoPath = true)
{
    if (currenWhenNoPath && !path)
        return current;

    Array* words = toArray(path);
    Node * node;
    if (path[0] == '/')
    {
        node = findNode(root, words, onlyDir);
    }
    else
    {
        node = findNode(current, words, onlyDir);
    }

    deleteWords(words);
    return node;
}

void ls(char* path)
{
    Node* curr = getNode(path, false);
    if (!curr)
    {
        errNoPath();
        return;
    }
    if (!isDir(curr))
        print(curr);
    else
        for (int i = 0; i < curr->childs->size; i++)
            print(curr->childs->arr[i]);
}
void pwd()
{
    print(current);
}

void cd(char* path)
{
    if (!strlen(path))
    {
        errNoArgs();
        return;
    }

    Node * node = getNode(path);
    if (!node)
        errNoPath();
    else if (!isDir(node))
        errNotDir();
    else
        current = node;
    
}

int findChild(Childs* childs, Node* node)
{
    for (int i = 0; i < childs->size; i++)
    {
        Node * c = childs->arr[i];
        if (strcmp(c->name, node->name) == 0)
            return i;
    }
    return childs->size;
}

void mvcp(char* firstArg, char* secondArg, void function(Node* first, Node* second))
{
    if (strlen(firstArg) == 0)
    {
        errNoArgs();
        return;
    }

    Node* first = getNode(firstArg, false, false);
    Node* second = getNode(secondArg, false);

    if (!first)
    {
        errNoSrcFile();
        return;
    }
    else if (isDir(first))
    {
        errSrcDir();
        return;
    }

    int i = findChild(second->childs, first);
    if (i < second->childs->size)
    {
        Node* removed = second->childs->arr[i];
        removeChild(second->childs, i);
        removeNode(removed);
    }

    function(first, second);
}


void mv(Node * first, Node* second)
{    
    addChild(second->childs, first);
    removeChild(first->parent->childs, findChild(first->parent->childs, first));
    first->parent = second;
}

void cp(Node * first, Node* second)
{
    addChild(second->childs, createNode(first->name, second));
}

bool checkName(char name[256], char* search)
{
    for (int i = 0; i < (int)strlen(search); )
    {
        if (name[i] == search[i])
        {
            i++;
            continue;
        }
        else if (search[i] == '*')
        {
            for (int j = i + 1; j < (int)strlen(name); j++)
                if (checkName(name + j, search + i + 1))
                    return true;
            return false;
        }
        else
            return false;
    }
    return true;
}

void _find(Node* curr, char* search)
{
    if (!isDir(curr) && checkName(curr->name, search))
        print(curr);

    for (int i = 0; i < curr->childs->size; i++)
    {
        Node* n = curr->childs->arr[i];
        _find(n, search);
    }
}

void find(char* firstArg, char* secondArg)
{
    Node* node = getNode(secondArg);
    if (!node)
        errNoPath();
    else
        _find(node, firstArg);
}

void processCommand(char * command, char* firstArg, char* secondArg)
{
    if (command)
        printf("$%s", command);
    else
        return;
    if (firstArg)
        printf(" %s", firstArg);
    if (secondArg)
        printf(" %s", secondArg);
    printf("\n");

    if (strcmp(command, "pwd") == 0)
        pwd();
    else if (strcmp(command, "cd") == 0)
        cd(firstArg);
    else if (strcmp(command, "ls") == 0)
        ls(firstArg);
    else if (strcmp(command, "mv") == 0)
        mvcp(firstArg,secondArg,&mv);
    else if (strcmp(command, "cp") == 0)
        mvcp(firstArg, secondArg, &cp);
    else if (strcmp(command, "find") == 0)
        find(firstArg, secondArg);
    else
        printf("ERROR unknown command\n");
}

void parseCommand(char* line)
{
    char** args = (char**)malloc(sizeof(char*) * 3);
    for (int i = 0; i < 3; i++)
        args[i] = nullptr;

    int loaded = -1;
    bool string = false;
    for (int i = 0; i < (int)strlen(line); i++)
    {
        if (line[i] > ' ')
        {
            if (!string)
            {
                loaded++;
                string = true;
            }
            args[loaded] = append(args[loaded], line[i]);
        }
        else
            string = false;
    }

    processCommand(args[0], args[1], args[2]);

    for (int i = 0; i < 3; i++)
    {       
        if (args[i])
            clear(args[i]);
    }

    free(args);
    
}

void load(FILE* in, void(function)(char*))
{
    char c;
    char* line = nullptr;
    while ((c = getc(in)) != EOF)
    {
        if (c == '\r')
            continue;

        if (c == '\n')
        {
            if (line)
            {
                function(line);
                line = clear(line);
            }
        }
        else
            line = append(line, c);
    }
    line = clear(line);
}

int main(int nr, char** args)
{
    if (nr < 3)
    {
        printf("Wrong number of arguments.");
        return 1;
    }

    FILE * fs = fopen(args[1], "r");
    FILE * commands = fopen(args[2], "r");
    if (!fs)
    {
        printf("Could not open filesystem file.");
        return 1;
    }
    if (!commands)
    {
        printf("Could not open commands file.");
        fclose(fs);
        return 1;
    }

    root = createNode("/");
    current = root;
    load(fs, &processFilesystem);
    fclose(fs);
    load(commands, &parseCommand);
    fclose(commands);
    removeNode(root);
#ifdef WIN32
    system("pause");
#endif
    return 0;
}

