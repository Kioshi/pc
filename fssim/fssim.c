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
        printf("%s\n", curr->name);
    else
    {
        int i;
        Childs* childs;
        childs = copyAndSortChilds(curr->childs);
        for (i = 0; i < childs->size; i++)
            print(childs->arr[i], true);
        removeChilds(childs, false);
    }
}

void pwd()
{
    print(current, true);
}

void cd(char* path)
{
    Node * node;
    if (!path || !strlen(path))
    {
        errNoArgs();
        return;
    }

    node = getNode(path, true, true);
    if (!node)
        errNoPath();
    else if (!isDir(node))
        errNotDir();
    else
        current = node;
    
}

int findChild(Childs* childs, Node* node)
{
    int i;
    for (i = 0; i < childs->size; i++)
    {
        Node * c = childs->arr[i];
        if (strcmp(c->name, node->name) == 0)
            return i;
    }
    return childs->size;
}

void mvcp(char* firstArg, char* secondArg, void function(Node* first, Node* second))
{
    Node* first;
    Node* second;
    int i;

    if (!firstArg || strlen(firstArg) == 0)
    {
        errNoArgs();
        return;
    }

    first = getNode(firstArg, false, false);
    second = getNode(secondArg, false, true);
    if (!second)
        second = current;

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

    if (first->parent == second)
        return;

    i = findChild(second->childs, first);
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
    if (!first->parent)
    {
        errNoPath();
        return;
    }
    addChild(second->childs, first);
    removeChild(first->parent->childs, findChild(first->parent->childs, first));
    first->parent = second;
}

void cp(Node * first, Node* second)
{
    addChild(second->childs, createNode(first->name, second));
}

bool checkName(char name[257], char* search)
{
    int i;
    for (i = 0; i < (int)strlen(search); )
    {
        if (name[i] == search[i])
        {
            i++;
            continue;
        }
        else if (search[i] == '*')
        {
            int j;
            for (j = i; j < (int)strlen(name); j++)
                if (checkName(name + j, search + i + 1))
                    return true;
            return false;
        }
        else
            return false;
    }
    
    return i == strlen(name) || search[strlen(search)-1] == '*';
}

void _find(Node* curr, char* search, Childs * childs)
{
    int i;
    if (!isDir(curr) && checkName(curr->name, search))
    {
        addChild(childs, curr);
    }

    for (i = 0; i < curr->childs->size; i++)
    {
        Node* n = curr->childs->arr[i];
        _find(n, search, childs);
    }
}

void find(char* firstArg, char* secondArg)
{
    Node* node = getNode(secondArg, true, true);
    if (!firstArg)
        errNoArgs();
    else if (!node)
        errNoPath();
    else
    {
        Childs* childs = createChilds(); 
        Childs* sorted;
        _find(node, firstArg, childs);
        sorted = copyAndSortChilds(childs);
        if (childs->size == 0)
            printf("\n");
        else
        {
            int i;
            for (i = 0; i < sorted->size; i++)
                print(sorted->arr[i], true);
        }

        removeChilds(childs, false);
        removeChilds(sorted, false);
    }
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
