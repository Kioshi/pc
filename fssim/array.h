#ifndef ARRAY_H
#define ARRAY_H

/**
* @file    array.h
* @author  Stepan Martinek <smartine@students.zcu.cz>
*
* @brief Contains Array struct and functions that manipulate with it
*/

typedef struct array
{
    int size;
    char** string;
} Array;


/**
* @fn Array* createArray();
*
* @brief Allocate and clean Array struct
*
* @return Array struct
*/
Array* createArray();

/**
* @fn Array* toArray(char* string);
*
* @brief Parse string to array of substrings by delimiter /
*
* @param string Field of chars to parse
* @return Array struct
*/
Array* toArray(char* string);

/**
* @fn void push_back(Array* words, char* s);
*
* @brief Append string to end of Array
*
* @param words Array struct containing array of strings.
* @param s Field of characters.
*/
void push_back(Array* words, char* s);

/**
* @fn void pop_front(Array* words);
*
* @brief Remove first item from Array
*
* @param words Array struct containing array of strings.
*/
void pop_front(Array* words);

/**
* @fn void deleteWords(Array* words);
*
* @brief Free every resource of Array
*
* @param words Array struct containing array of strings.
*/
void deleteWords(Array* words);

int wss;
int arrays;
#endif /* ARRAY_H */
