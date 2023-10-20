#include "shell.h"

void processCustomCommand(char *command __attribute__((unused)))

{
    /* Implementation of processCustomCommand*/



{
    char *args[MAX_ARGS];
    int argCount;
    int i = 0;
    int result = 1;

    parseCustomInput(command, args, &argCount);


    if (argCount == 0)
        return;

    while (args[i] != NULL)
    {
        if (strcmp(args[i], "&&") == 0)
        {
            if (result == 0)
                break;
        }
        else if (strcmp(args[i], "||") == 0)
        {
            if (result != 0)
                break;
        }
        else
        {
            result = executeCustomSingleCommand(args + i);
        }
        i++;
    }

    free(args[0]);
}

    return *argCount;
}

