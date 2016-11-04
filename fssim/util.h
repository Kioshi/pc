#pragma once

#include<stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef S_SPLINT_S
#include <malloc.h>
#endif

#pragma warning(disable: 4996) // _CRT_SECURE_NO_WARNINGS
#define nullptr 0

typedef enum
{
    false,
    true
} bool;

void* _calloc(size_t count, size_t size);
void* _malloc(size_t size);

enum returnCodes
{
    OK,
    MALLOC_FAIL,
    WRONG_ARGUMENTS,
    NO_FILESYSTEM,
    NO_COMMANDS
};