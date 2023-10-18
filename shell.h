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

unsigned int match_char(char c, const char *str);
char *custom_strtok(char *str, const char *delim);
int execute_single_command(char **args);
char *combine_paths(void);
void print_error(char *command);
void handle_internal_command(char **args);
void handle_external_command(char **args);
void display_prompt(void);
void process_command(char *command);
int parse_input(char *input, char **args);
void handle_built_in_commands(char **args);
void execute_external_command(char **args);
void print_environment(void);
void displayPrompt(void);
void processCommand(char *command);

#endif /* SHELL_H */
