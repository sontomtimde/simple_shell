#include "shell.h"

/**
 * match_char - Checks if a character matches any in a string.
 * @c: Character to check.
 * @str: String to check.
 *
 * Return: 1 if match, 0 if not.
 */
unsigned int match_char(char c, const char *str)
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
 * custom_strtok - Custom strtok-like function.
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
        if (match_char(next[i], delim) == 0)
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
        if (match_char(next[i], delim) == 1)
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

/**
 * execute_single_command - Executes a single command and returns the exit status.
 * @args: An array of command arguments.
 * Return: The exit status of the command.
 */
int execute_single_command(char **args)
{
    pid_t child_pid = fork();

    if (child_pid < 0)
    {
        perror("Fork error");
        return 1;
    }
    else if (child_pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("Execution error");
            exit(2);
        }
    }
    else
    {
        int child_status;
        waitpid(child_pid, &child_status, 0);

        if (WIFEXITED(child_status))
        {
            int exit_status = WEXITSTATUS(child_status);
            return exit_status;
        }
        else if (WIFSIGNALED(child_status))
        {
            int terminating_signal = WTERMSIG(child_status);
            (void)terminating_signal;
            return 1;
        }
    }
    return 0;
}
