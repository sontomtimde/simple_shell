#include "shell.h"

/**
 * customMatching - Checks if a character matches any in a string.
 * @c: Character to check.
 * @str: String to check.
 *
 * Return: 1 if there's a match, 0 if not.
 */
unsigned int customMatching(char c, const char *str)
{
    unsigned int i;

    for (i = 0; str[i] != '\0'; i++)
    {
        if (c == str[i])
            return 1;
    }
    return 0;
}

/**
 * custom_strtok - Custom strtok-like function for the custom shell.
 * @str: String to tokenize.
 * @delim: Delimiter to tokenize against.
 *
 * Return: Pointer to the next token or NULL.
 */
char *custom_strtok(char *str, const char *delim)
{
    static char *token;
    static char *next;
    unsigned int i;

    if (str != NULL)
        next = str;

    token = next;

    if (token == NULL)
        return NULL;

    for (i = 0; next[i] != '\0'; i++)
    {
        if (customMatching(next[i], delim) == 0)
            break;
    }

    if (next[i] == '\0' || next[i] == '#')
    {
        next = NULL;
        return NULL;
    }

    token = next + i;
    next = token;

    for (i = 0; next[i] != '\0'; i++)
    {
        if (customMatching(next[i], delim) == 1)
            break;
    }

    if (next[i] == '\0')
        next = NULL;
    else
    {
        next[i] = '\0';
        next = next + i + 1;

        if (*next == '\0')
            next = NULL;
    }

    return token;
}

