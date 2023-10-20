#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

typedef struct Alias
{
	char *name;
	char *value;
	struct Alias *next;
} Alias;

Alias *alias_list = NULL;

void parse_command(char *command, char *args[MAX_ARGS]);
void execute_command(char *args[MAX_ARGS]);
void add_alias(char *name, char *value);
int resolve_alias(char *name, char *resolved, size_t size);
void list_env_variables();

int main(int argc, char *argv[]);

#endif /* SHELL_H */
