#pragma once

typedef struct array
{
    int size;
    char** string;
} Array;


Array* createArray();

void push_back(Array* words, char* s);

Array* toArray(char* string);

void pop_front(Array* words);

void deleteWords(Array* words);