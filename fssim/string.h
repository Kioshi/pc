#ifndef STRING_H
#define STRING_H
#include <string.h>

/**
* @file    string.h
* @author  Stepan Martinek <smartine@students.zcu.cz>
*
* @brief Contains function for working with char array as with string
*/

/**
* @fn append(char* string, char c)
* @brief Appends c to field of characters
*
* @param string Field of characters.
* @param c Character to append.
* @return Field of characters with appended c
*/
char * append(char* string, char c);

/**
* @fn char * clear(char* string);
*
* @brief Free string and return null pointer
*
* @param string Field of characters.
* @return Null pointer
*/
char * clear(char* string);

/**
* @fn int compare(char * a, char * b);
*
* @brief Compare strings by groups and characters in groups, returns 0 for same -1 for a < b and 1 for b >1
* @param a string a
* @param b string b
*
* @return Returns comparsion result
*/
int compare(char * a, char * b);

/**
* @fn int getGroup(char c);
*
* @brief Returns group according to character / = 0, a-z = 1, A-Z = 2, 0-9 - 3
* @param c character
*
* @return Returns  group id
*/
int getGroup(char c);

/**
* @fn int wordLen(size_t start, char * string);
*
* @brief Return dir/file lenght
* @param start starting index
* @param string word
*
* @return Returns  group id
*/
int wordLen(size_t start, char * string);

#endif /* STRING_H */
