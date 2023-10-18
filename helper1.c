#include "shell.h"


void executeExternal(char **args)
{
	char *combinedPath = combinePaths();
	pid_t childPid;

	if (combinedPath == NULL)
	{
		printError(args[0]);
		exit(127);
	}

	childPid = fork();
	if (childPid < 0)
	{
		perror("Fork error");
		free(combinedPath);
		exit(1);
	}
	else if (childPid == 0)
	{
		executeChildProcess(args);
	}
	else
	{
		handleParentProcess(childPid);
	}
	free(combinedPath);
}

void executeChildProcess(char **args)
{
	if (setPathEnvironment())
	{
		execvp(args[0], args);
		perror("Execution error");
		exit(2);
	}
}

int setPathEnvironment()
{
	if (getenv("PATH") == NULL)
	{
		setenv("PATH", "/usr/bin:/bin", 1);
		return 1;
	}
	return (0);
}

void handleParentProcess(pid_t childPid)
{
	int childStatus;

	waitpid(childPid, &childStatus, 0);
	if (WIFEXITED(childStatus))
	{
		int exitStatus = WEXITSTATUS(childStatus);
		(void)exitStatus;
	}
	else if (WIFSIGNALED(childStatus))
	{
		int terminatingSignal = WTERMSIG(childStatus);
		(void)terminatingSignal;
	}
}
void handleInternalCommand(char **args)
{
	if (strcmp(args[0], "exit") == 0)
	{
		handleExit(args);
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		handleCd(args);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		handleEnv();
	}
	else if (strcmp(args[0], "setenv") == 0)
	{
		handleSetEnv(args);
	}
	else if (strcmp(args[0], "unsetenv") == 0)
	{
		handleUnsetEnv(args);
	}
	else
	{
		executeExternal(args);
	}
}
