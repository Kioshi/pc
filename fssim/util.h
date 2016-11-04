#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>


/**
* @file    util.h
* @author  Stepan Martinek <smartine@students.zcu.cz>
*
* @brief Contains utility enum, macros and calloc, malloc wrappers
*/

/* Disable Visual studio warning propagating their functions */
#pragma warning(disable: 4996) /* _CRT_SECURE_NO_WARNINGS */

/* Define for easier transfer from c++ */
#define nullptr 0

/* Define for easier transfer from c++ */
typedef enum
{
    false = 0,
    true
} bool;

/**
* @fn void* _calloc(size_t count, size_t size);
*
* @brief Wrapper for calloc that will terminate program with proper error code if no memory is available
*
* @param count Count of sized blocks
* @param size Size of allocated block
* @return Pointer to newly allocated memory
*/
void* _calloc(size_t count, size_t size);

/**
* @fn void* _malloc(size_t size);
*
* @brief Wrapper for malloc that will terminate program with proper error code if no memory is available
*
* @param size Size of newly allocated memory
* @return Pointer to newly allocated memory
*/
void* _malloc(size_t size);

/* Return codes, for fatal errors */
enum returnCodes
{
    OK = 0,
    MALLOC_FAIL,
    WRONG_ARGUMENTS,
    NO_FILESYSTEM,
    NO_COMMANDS
};

#endif /* UTIL_H */