#include "shell.h"
void handleEnv(void)
{
	printEnvironment();
}

void processCommand(char *command)
{
	char *args[MAX_ARGS];
	int argCount;
	int i, result;

	argCount = parse_input(command, args);

	if (argCount == 0)
	{
		return;
	}

	i = 0;
	result = 1;

	while (args[i] != NULL)
	{
		if (strcmp(args[i], "&&") == 0)
		{
			result = executeAndCommands(args, i, result);
		}
		else if (strcmp(args[i], "||") == 0)
		{
			result = executeOrCommands(args, i, result);
		}
		else
		{
			result = executeSingleCommand(args + i);
		}
		i++;
	}
	free(args[0]);
}

int executeAndCommands(char **args, int i, int result)
{
	if (result == 0)
	{
		return (1);
	}
	return (executeSingleCommand(args + i));
}

int executeOrCommands(char **args, int i, int result)
{
	if (result != 0)
	{
		return (0);
	}
	return executeSingleCommand(args + i);
}

int parse_input(char *input, char **args)
{
	int argCount = 0;
	char *token;

	token = strtok(input, " ");

	while (token != NULL && argCount < MAX_ARGS - 1)
	{
		args[argCount++] = token;
		token = strtok(NULL, " ");
	}
	args[argCount] = NULL;

	return (argCount);
}
