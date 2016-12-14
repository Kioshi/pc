#include "fssim.h"
#include "string.h"

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

/**
* @fn void processFilesystem(char* line)
*
* @brief Parse and insert nodes from line
*
* @param line Line to parse
*/
void processFilesystem(char* line)
{
    Array* words = toArray(line);
    if (words->size && strcmp(words->string[0], "/") == 0)
        pop_front(words);

    insert(root, words);
    deleteWords(words);
}

/**
* @fn void parseCommand(char* line)
*
* @brief Parse command and its arguments from line
*
* @param line Line to parse
*/
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

/**
* @fn void load(FILE* in, void(function)(char*))
*
* @brief Load row from specified file and executed specified functions with it.
*
* @param in File to load from
* @param function Function to execute
*/
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
    if (line)
    {
        function(line);
    }
    line = clear(line);
}

/**
* @fn int main(int nr, char** args)
*
* @brief Check arguments and load file system, then load and execute commands
*
* @param nr Number of arguments
* @param args Field of strings
* @return Returns zero if OK
*/
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
        if (commands)
            fclose(commands);
        printf("Could not open filesystem file.\n");
        return NO_FILESYSTEM;
    }
    if (!commands)
    {
        fclose(fs);
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
    root = nullptr;
    current = nullptr;
    return OK;
}

