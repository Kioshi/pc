#ifndef STRING_H
#define STRING_H

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

#endif /* STRING_H */
