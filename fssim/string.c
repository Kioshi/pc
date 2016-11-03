#include "string.h"
#include "util.h"

char * append(char* string, char c)
{
    if (!string)
        string = (char*)_calloc(2, sizeof(char));
    else
    {
        char* tmp = (char*)_calloc(strlen(string) + 2, sizeof(char));
        memcpy(tmp, string, strlen(string));
        free(string);
        string = tmp;
    }
    string[strlen(string)] = c;
    return string;
}

char * clear(char* string)
{
    if (string)
        free(string);
    return nullptr;
}