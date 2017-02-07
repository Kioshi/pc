#ifndef FSSIM_H
#define FSSIM_H

#include "util.h"
#include "node.h"

/**
* @file    fssim.h
* @author  Stepan Martinek <smartine@students.zcu.cz>
*
* @brief Contains simulated commands
*/

/**
* @fn void errNoArgs();
*
* @brief Print no arguments error
*/
void errNoArgs();

/**
* @fn void errNoPath();
*
* @brief Print no path error
*/
void errNoPath();

/**
* @fn void errNotDir();
*
* @brief Print not a directory error
*/
void errNotDir();

/**
* @fn void errNoSrcFile();
*
* @brief Print no source file error
*/
void errNoSrcFile();

/**
* @fn void errSrcDir();
*
* @brief Print source directory error
*/
void errSrcDir();

/**
* @fn void ls(char* path);
*
* @brief Simulate behavior of ls command
* @param path String cointaining path
*/
void ls(char* path);

/**
* @fn void pwd();
*
* @brief Simulate behavior of pwd command
*/
void pwd();

/**
* @fn void cd(char* path);
*
* @brief Simulate behavior of cd command
* @param path String cointaining path
*/
void cd(char* path);

/**
* @fn int findChild(Childs* childs, Node* node);
*
* @brief Find index of node in childs
* @param childs Childs where we are looking
* @param node Node we are looking for
*
* @return Returns index of node
*/
int findChild(Childs* childs, Node* node);

/**
* @fn void mvcp(char* firstArg, char* secondArg, void function(Node* first, Node* second));
*
* @brief Executes same instructions for mv and cp then call proper function
* @param firstArg string with path to first node
* @param secondArg string with path to second node
* @param function function to call, cp or mv
*/
void mvcp(char* firstArg, char* secondArg, void function(Node* first, Node* second));

/**
* @fn void mv(Node* first, Node* second);
*
* @brief Simulate behavior of mv command
* @param first Node to move
* @param second Node to move into
*/
void mv(Node* first, Node* second);

/**
* @fn void cp(Node* first, Node* second);
*
* @brief Simulate behavior of cp command
* @param first Node to copy
* @param second Node to copy into
*/
void cp(Node* first, Node* second);

/**
* @fn bool checkName(char name[], char* search);
*
* @brief Check if names matching with wild-cards
* @param name Name of node
* @param search Search to compare with
*
* @return Returns true if name matches
*/
bool checkName(char name[], char* search);

/**
* @fn void _find(Node* curr, char* search);
*
* @brief Find and print nodes, if not found anything prints empty line
* @param curr Root of search
* @param search Search to compare name with
* @param childs Childs to copy nodes into
*
*/
void _find(Node* curr, char* search, Childs * childs);

/**
* @fn void find(char* firstArg, char* secondArg);
*
* @brief Simulate behavior of find command
* @param firstArg Path to root node
* @param secondArg Search "regex"
*/
void find(char* firstArg, char* secondArg);

/**
* @fn void processCommand(char* command, char* firstArg, char* secondArg);
*
* @brief Determine what command to use
* @param command Command identificator
* @param firstArg First argument of command, can be null
* @param secondArg Second argument of command, can be null
*/
void processCommand(char* command, char* firstArg, char* secondArg);

#endif /* FSSIM_H */
