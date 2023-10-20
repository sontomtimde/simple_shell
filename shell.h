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

unsigned int customMatching(char c, const char *str);
char *custom_strtok(char *str, const char *delim);
int executeCustomSingleCommand(char **args);
char *combineCustomPaths(void);
void printCustomError(char *command);
void handleCustomInternalCommand(char **args);
void handleCustomExternalCommand(char **args);
void displayCustomPrompt(void);
int parseCustomInput(char *input, char **args, int *argCount);
void handleCustomBuiltInCommands(char **args);
void executeCustomExternalCommand(char **args);
void printCustomEnvironment(void);
void processCustomCommand(char *command, int length);

#endif /*SHELL_H */

