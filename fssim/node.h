#ifndef NODE_H
#define NODE_H

#include "util.h"
#include "array.h"

/**
* @file    node.h
* @author  Stepan Martinek <smartine@students.zcu.cz>
*
* @brief Contains Node and Childs structs and functions that manipulate with them
*/

typedef struct childs
{
    int size;
    struct node** arr;
} Childs;

struct node
{
    char name[257];
    struct node* parent;
    Childs* childs;
};
typedef struct node Node;

/* Pointer to root */
extern Node* root;
/* Pointer to current node */
extern Node* current;

/**
* @fn void print(Node * node, bool last);
*
* @brief Print absolute path to node
*
* @param node Node to print
* @param last Indication for printing of new line
*/
void print(Node * node, bool last);

/**
* @fn Node * createNode(char name[], Node* parent);
*
* @brief Create and return node
* @param name Name of node
* @param parent Parent of node, if null node will set it self as parent (root)
*
* @return Returns new Node struct
*/
Node * createNode(char name[], Node* parent);

/**
* @fn void removeNode(Node* curr);
*
* @brief Free resources of node
* @param curr Node to free
*/
void removeNode(Node* curr);

/**
* @fn Childs* createChilds();
*
* @brief Create childs struct
*
* @return Returns new Childs struct
*/
Childs* createChilds();

/**
* @fn void addChild(Childs* childs, Node * node);
*
* @brief Add note to childs struct
* @param childs Childs struct where to add node
* @param node Node to add
*/
void addChild(Childs* childs, Node * node);

/**
* @fn int cmp(const void* pA, const void* pB);
*
* @brief Comparator function for qsort which extract Nodes, their absolute names and uses compare function on them.
* @param pA const pointer to Node** array
* @param pB const pointer to Node** array
*
* @return Returns result of compare function with nodes absolute name.
*/
int cmp(const void* pA, const void* pB);

/**
* @fn Childs * copyAndSortChilds(Node*curr);
*
* @brief Make shallow copy of childs sorted by names, as sorting algorithm is used qsort from C standard library
* @param childs Childs to copy
*
* @return Return shallow copy of childs
*/
Childs * copyAndSortChilds(Childs* childs);

/**
* @fn void removeChild(Childs* childs, int index);
*
* @brief Remove node on index from childs structure
* @param childs Childs struct from where to remove node
* @param index Position of node to remove
*/
void removeChild(Childs* childs, int index);

/**
* @fn void removeChilds(Childs* childs, bool removeNodes);
*
* @brief Free resources of child, if removeNodes is true also calls removeNode for each child
* @param childs Childs to free
* @param removeNodes Decides if only free struct or child nodes too
*/
void removeChilds(Childs* childs, bool removeNodes);

/**
* @fn bool isDir(Node * node);
*
* @brief Determine if node is dir.
* @param node Node to determine
*
* @return Returns true if last character of dir is /
*/
bool isDir(Node * node);

/**
* @fn void insert(Node* curr, Array* words);
*
* @brief Insert words to file system
* @param curr Current node
* @param words Array of words to insert
*/
void insert(Node* curr, Array* words);

/**
* @fn Node * findNode(Node * curr, Array* words, bool onlyDir);
*
* @brief Finds Node from specified array path
* @param curr Start of finding
* @param words Arrays of path
* @param onlyDir Bool deciding type of node we are looking for
*
* @return Returns found node, can be null
*/
Node * findNode(Node * curr, Array* words, bool onlyDir);

/**
* @fn Node* getNode(char* path, bool onlyDir, bool currenWhenNoPath);
*
* @brief Find and returns node by string path
* @param path String cointaining path
* @param onlyDir Bool deciding type of node we are looking for
* @param currenWhenNoPath Bool deciding if we use current node when path is not specified
*
* @return Returns node, can be null
*/
Node* getNode(char* path, bool onlyDir, bool currenWhenNoPath);

/**
* @fn char* getAbsoluteName(char* string, Node * node);
*
* @brief Recursively build absolute path
* @param string Current name string
* @param node Current node
*
* @return Returns absolute path string
*/
char* getAbsoluteName(char* string, Node * node);

#endif /* NODE_H */
