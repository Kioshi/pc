#pragma once
#include "util.h"
#include "array.h"

typedef struct childs
{
    int size;
    struct node** arr;
} Childs;

struct node
{
    char name[256];
    struct node* parent;
    Childs* childs;
};
typedef struct node Node;

Node* root;
Node* current;

void print(Node * node, bool last);

Childs* createChilds();

Node * createNode(char name[256], Node* parent);
void removeNode(Node* curr);

void removeChilds(Childs* childs, bool removeNodes);
Childs * copyAndSortChilds(Node*curr);

void addChild(Childs* childs, Node * node);

void removeChild(Childs* childs, int index);

bool isDir(Node * node);

void insert(Node* curr, Array* words);


Node * findNode(Node * curr, Array* words, bool onlyDir);

Node* getNode(char* path, bool onlyDir, bool currenWhenNoPath);