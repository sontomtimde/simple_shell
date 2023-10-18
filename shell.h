#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_ARGS 1024

extern char **environ;
void executeExternal(char **args);
void executeChildProcess(char **args);
int setPathEnvironment(void);
void handleParentProcess(pid_t childPid);
void handleInternalCommand(char **args);
void handleSetEnv(char **args);
void handleUnsetEnv(char **args);
void handleExternalCommand(char **args);
void handleExit(char **args);
void handleCd(char **args);
void handleEnv(void);
void processCommand(char *command);
int executeAndCommands(char **args, int i, int result);
int executeOrCommands(char **args, int i, int result);
int parse_input(char *input, char **args);
void handleBuiltInCommands(char **args);
void executeExternalCommand(char **args);
void printEnvironment(void);
char *combinePaths(void);
void printError(char *command);
void displayPrompt(void);
int executeSingleCommand(char **args);

#endif /* SHELL_H */
