#ifndef FSSIM_H
#define FSSIM_H

#include "util.h"
#include "node.h"

extern Node* root;
extern Node* current;

void errNoArgs();
void errNoPath();
void errNotDir();
void errNoSrcFile();
void errSrcDir();

void ls(char* path);
void pwd();

void cd(char* path);

int findChild(Childs* childs, Node* node);

void mvcp(char* firstArg, char* secondArg, void function(Node* first, Node* second));

void mv(Node* first, Node* second);
void cp(Node* first, Node* second);

bool checkName(char name[], char* search);

int _find(Node* curr, char* search);

void find(char* firstArg, char* secondArg);

void processCommand(char* command, char* firstArg, char* secondArg);

#endif /* FSSIM_H */
