#include "util.h"


void* _calloc(size_t count, size_t size)
{
    void* mem = calloc(count, size);
    if (mem == nullptr)
    {
        printf("Out of memory!\n");
        exit(MALLOC_FAIL);


    return mem;
}

void* _malloc(size_t size)
{    
    void* mem = malloc(size);
    if (mem == nullptr)
    {
        printf("Out of memory!\n");
        exit(MALLOC_FAIL);
    }
    return mem;
}