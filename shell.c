#include "shell.h"

int main(void)
{
    char *user_input = NULL;
    size_t input_size = 0;
    char *command = NULL;
    int command_size = 0;

    while (1)
    {
        displayCustomPrompt();

        if (getline(&user_input, &input_size, stdin) == -1)
        {
            if (feof(stdin))
                break;

            printCustomError("Input error");
            clearerr(stdin);
            free(user_input);
            continue;
        }

        if (user_input[0] == '\n')
        {
            free(user_input);
            continue;
        }

        if (user_input[0] != '#')
        {
            int command_length = parseCustomInput(user_input, &command, &command_size);
            if (command_length > 0)
                processCustomCommand(command, command_length);
        }

        free(user_input);
    }

    return 0;
}

