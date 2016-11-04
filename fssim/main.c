#include "fssim.h"

/**
* @file    main.c
* @author  Stepan Martinek <smartine@students.zcu.cz>
*
* @brief Main file with data loading functions
*/


/**
* @mainpage  Fssim
*
* Simple filesystem simulation accepting commands: pwd, ls, cp mv, cd, find \n
* Term paper of Stepan Martinek for subject PC on FAV UWB.
* @author  Stepan Martinek <smartine@students.zcu.cz>
*/

void processFilesystem(char* line)
{
    Array* words = toArray(line);
    if (words->size && strcmp(words->string[0], "/") == 0)
        pop_front(words);

    insert(root, words);
    deleteWords(words);
}

void parseCommand(char* line)
{
    char** args = (char**)malloc(sizeof(char*) * 3);
    int i;
    int loaded = -1;
    bool string = false;
    for (i = 0; i < 3; i++)
        args[i] = nullptr;

    for (i = 0; i < (int)strlen(line); i++)
    {
        if (line[i] > ' ')
        {
            if (!string)
            {
                loaded++;
                string = true;
            }
            args[loaded] = append(args[loaded], line[i]);
        }
        else
            string = false;
    }

    processCommand(args[0], args[1], args[2]);

    for (i = 0; i < 3; i++)
    {
        if (args[i])
            clear(args[i]);
    }

    free(args);

}

void load(FILE* in, void(function)(char*))
{
    char c;
    char* line = nullptr;
    while ((c = getc(in)) != EOF)
    {
        if (c == '\r')
            continue;

        if (c == '\n')
        {
            if (line)
            {
                function(line);
                line = clear(line);
            }
        }
        else
            line = append(line, c);
    }
    line = clear(line);
}

int main(int nr, char** args)
{
    FILE* fs, *commands;
    if (nr < 3)
    {
        printf("Wrong number of arguments.\n");
        return WRONG_ARGUMENTS;
    }

    fs = fopen(args[1], "r");
    commands = fopen(args[2], "r");
    if (!fs)
    {
        printf("Could not open filesystem file.\n");
        return NO_FILESYSTEM;
    }
    if (!commands)
    {
        printf("Could not open commands file.\n");
        fclose(fs);
        return NO_COMMANDS;
    }

    root = createNode("/", nullptr);
    current = root;
    load(fs, &processFilesystem);
    fclose(fs);
    load(commands, &parseCommand);
    fclose(commands);
    removeNode(root);
    return OK;
}

