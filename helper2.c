#include "shell.h"

void handleSetEnv(char **args)
{
	if (args[1] != NULL && args[2] != NULL)
	{
		if (setenv(args[1], args[2], 1) != 0)
		{
			perror("setenv error");
		}
	}
	else
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
	}
	free(args);
}

void handleUnsetEnv(char **args)
{
	if (args[1] != NULL)
	{
		if (unsetenv(args[1]) != 0)
		{
			perror("unsetenv error");
		}
	}
	else
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
	}
	free(args);
}
void handleExternalCommand(char **args)
{
	executeExternal(args);
}

void handleExit(char **args)
{
	if (args[1] != NULL)
	{
		int exitStatus = atoi(args[1]);

		free(args);
		exit(exitStatus);
	}
	else
	{
		free(args);
		exit(EXIT_SUCCESS);
	}
}

void handleCd(char **args)
{
	if (args[1] != NULL)
	{
		if (chdir(args[1]) != 0)
			perror("cd error");
	}
	else
	{
		fprintf(stderr, "Usage: cd <directory>\n");
	}
	free(args);
}
