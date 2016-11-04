#ifndef ARRAY_H
#define ARRAY_H

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

#endif /* ARRAY_H */
