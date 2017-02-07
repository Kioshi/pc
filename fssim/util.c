#include "util.h"


void* my_calloc(size_t count, size_t size)
{
    void* mem = calloc(count, size);
    if (mem == nullptr)
        printf("Out of memory!\n");

    return mem;
}

void* my_malloc(size_t size)
{    
    void* mem = malloc(size);
    if (mem == nullptr)
        printf("Out of memory!\n");

    return mem;
}