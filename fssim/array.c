#include "array.h"
#include "util.h"

Array* createArray()
{
    Array* arr = (Array*)_malloc(sizeof(Array));
    arr->size = 0;
    arr->string = nullptr;
    return arr;
}

void push_back(Array* words, char* s)
{
    char** tmp = (char**)_calloc((size_t)(words->size + 1), sizeof(char*));
    char* string;
    if (words->string)
    {
        int i;
        for (i = 0; i < words->size; i++)
            tmp[i] = words->string[i];
        free(words->string);
        words->string = nullptr;
    }
    words->string = tmp;
    string = (char*)_calloc((strlen(s) + 1), sizeof(char));
    strcpy(string, s);
    words->string[words->size++] = string;
}

Array* toArray(char* string)
{
    char s[256];
    int curr = 0;
    Array* words = createArray();
    int i;
    memset(s, 0, sizeof(s));
    for (i = 0; i < (int)strlen(string); i++)
    {
        if (curr == 256)
        {
            memset(s, 0, sizeof(s));
            curr = 0;
        }

        s[curr++] = string[i];
        if (string[i] == '/')
        {
            if (curr != 1)
                push_back(words, s);
            memset(s, 0, sizeof(s));
            curr = 0;
        }
    }
    if (strlen(s))
        push_back(words, s);

    return words;
}

void pop_front(Array* words)
{
    if (words->size == 0)
        return;

    free(words->string[0]);
    words->string[0] = nullptr;
    if (--words->size)
    {
        int i;
        for (i = 1; i < words->size + 1; i++)
            words->string[i - 1] = words->string[i];
    }
    else
    {
        free(words->string);
        words->string = nullptr;
    }
}


void deleteWords(Array* words)
{
    int i;

    if (!words)
        return;

    for (i = 0; i < words->size; i++)
        free(words->string[i]);
    if (words->string)
        free(words->string);
    free(words);
}
