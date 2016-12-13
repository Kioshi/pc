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

int getGroup(char c)
{
    if (c == '/')
        return 0;
    if (c >= 'a' && c <= 'z')
        return 1;
    if (c >= 'A' && c <= 'Z')
        return 2;
    if (c >= '0' && c <= '9')
        return 3;
    return 4;
}

int wordLen(size_t start, char * string)
{
    size_t i = start;
    for (; i < strlen(string); i++)
    {
		if (string[i] == '/')
		{
			i++;
			break;
		}
    }
    return i - start;

}

int compare(char * a, char * b)
{
    size_t i;
    for (i = 0; i < strlen(a) && i < strlen(b); i++)
    {
        if (a[i] != '/' || b[i] != '/')
        {
            int la, lb;
            la = wordLen(i, a);
            lb = wordLen(i, b);
            if (la != lb)
            {
                if (la < lb)
                    return  -1;
                return 1;
            }
        }
        char x, y;
        if (a[i] == b[i])
            continue;

        x = getGroup(a[i]);
        y = getGroup(b[i]);

        if (x != y)
        {
            if (x < y)
                return -1;
            return 1;
        }
        else
        {
            if (a[i] < b[i])
                return -1;
            else
                return 1;
        }
    }

    return 0;
}
