#include "fssim.h"

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


void ls(char* path)
{
    Node* curr = getNode(path, false, true);
    if (!curr)
    {
        errNoPath();
        return;
    }
    if (!isDir(curr))
        print(curr, true);
    else
        for (int i = 0; i < curr->childs->size; i++)
            print(curr->childs->arr[i], true);
}

void pwd()
{
    print(current, true);
}

void cd(char* path)
{
    if (!strlen(path))
    {
        errNoArgs();
        return;
    }

    Node * node = getNode(path, true, true);
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
    Node* second = getNode(secondArg, false, true);

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

void _find(struct Node* curr, char* search)
{
    if (!isDir(curr) && checkName(curr->name, search))
        print(curr, true);

    for (int i = 0; i < curr->childs->size; i++)
    {
        struct Node* n = curr->childs->arr[i];
        _find(n, search);
    }
}

void find(char* firstArg, char* secondArg)
{
    Node* node = getNode(secondArg, true, true);
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
