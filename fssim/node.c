#include "node.h"
#include "string.h"

void print(Node * node, bool last)
{
    if (node->parent)
        print(node->parent, false);
    printf("%s", node->name);

    if (last)
        printf("\n");
}

Node * createNode(char name[257], Node* parent)
{
    Node* node = (Node*)my_malloc(sizeof(Node));
    node->parent = parent;
    memset(node->name, 0, 257);
    strcpy(node->name, name);
    node->childs = createChilds();
    nodes++;
    return node;
}

void removeNode(Node* curr)
{
    if (!curr)
        return;

    removeChilds(curr->childs, true);
    free(curr);
    nodes--;
}

Childs* createChilds()
{
    Childs* childs = (Childs*)my_malloc(sizeof(Childs));
    childs->size = 0;
    childs->arr = nullptr;

    chs++;
    return childs;
}

void addChild(Childs* childs, Node * node)
{
    Node** tmp = (Node**)my_calloc(childs->size + 1, sizeof(Node*));
    if (childs->size > 0)
    {
        int i;
        for (i = 0; i < childs->size; i++)
            tmp[i] = childs->arr[i];
        free(childs->arr);
        childs->arr = nullptr;
    }
    childs->arr = tmp;
    childs->arr[childs->size++] = node;
}

char* getAbsoluteName(char* string, Node * node)
{
    size_t i;
    if (node->parent)
    {
        string = getAbsoluteName(string, node->parent);
    }
    for (i = 0; i < strlen(node->name); i++)
    {
        string = append(string, node->name[i]);
    }
    return string;  
    
}

Childs * copyAndSortChilds(Childs* old)
{
    Childs* childs = (Childs*)my_malloc(sizeof(Childs));
    chs++;
    int i;
    childs->size = old->size;
    childs->arr = (Node**)my_calloc(childs->size, sizeof(Node*));

    for (i = 0; i < childs->size; i++)
    {
        char*a = nullptr;
        char*b = nullptr;
        int j;
        for (j = 0; j < i; j++)
        {
            a = getAbsoluteName(nullptr,old->arr[i]);
            b = getAbsoluteName(nullptr,childs->arr[j]);
            if (compare(a, b) < 0)
            {
                int k;
                for (k = childs->size - 1; k > j; k--)
                    childs->arr[k] = childs->arr[k-1];
                childs->arr[j] = old->arr[i];
                break;
            }
            clear(a);
            clear(b);
            a = nullptr;
            b = nullptr;
        }
        clear(a);
        clear(b);
        if (j == i)
            childs->arr[j] = old->arr[i];
    }

    return childs;
}

void removeChild(Childs* childs, int index)
{
    int i;
    for (i = index + 1; i < childs->size; i++)
        childs->arr[i - 1] = childs->arr[i];

    childs->size--;
    if (childs->size == 0)
    {
        free(childs->arr);
        childs->arr = nullptr;
    }
}

void removeChilds(Childs* childs, bool removeNodes)
{
    int i;
    if (removeNodes)
    {
        for (i = 0; i < childs->size; i++)
        {
            if (childs->arr[i] != nullptr)
                removeNode(childs->arr[i]);
            childs->arr[i] = nullptr;
        }
    }
    if (childs->arr)
        free(childs->arr);
    childs->arr = nullptr;
    free(childs);
    chs--;
}

bool isDir(Node * node)
{
    return node->name[strlen(node->name) - 1] == '/';
}

void insert(Node* curr, Array* words)
{
    int i;
    Node* n;
    while (words->size > 0)
    {
        for (i = 0; i < curr->childs->size; i++)
        {
            Node* c;
            c = curr->childs->arr[i];
            if (strcmp(c->name, words->string[0]) == 0)
            {
                pop_front(words);
                insert(c, words);
                return;
            }
        }
        n = createNode(words->string[0], curr);
        addChild(curr->childs, n);
        curr = n;
        pop_front(words);
    }
}

Node * findNode(Node * curr, Array* words, bool onlyDir)
{
    char* currString;
    int i;

    if (!words->size)
        return curr;

    if (onlyDir && !isDir(curr))
        return curr;

    currString = (char*)my_calloc(strlen(words->string[0]) + 1, sizeof(char));
    strcpy(currString, words->string[0]);
    pop_front(words);
    while (strcmp(currString, "./") == 0 || strcmp(currString, ".") == 0)
    {
        if (!words->size)
        {
            free(currString);
            return curr;
        }

        pop_front(words);
        free(currString);
        currString = (char*)my_calloc(strlen(words->string[0]) + 1, sizeof(char));
        strcpy(currString, words->string[0]);
    }

    if (strcmp(currString, "../") == 0 || strcmp(currString, "..") == 0)
    {
        free(currString);
        if (!curr->parent)
            return nullptr;
        return findNode(curr->parent, words, onlyDir);
    }

    for (i = 0; i < curr->childs->size; i++)
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

Node* getNode(char* path, bool onlyDir, bool currenWhenNoPath)
{
    Array* words;
    Node * node;
    if (currenWhenNoPath && !path)
        return current;

    words = toArray(path);
    if (path[0] == '/')
        node = findNode(root, words, onlyDir);
    else
        node = findNode(current, words, onlyDir);

    deleteWords(words);
    return node;
}
