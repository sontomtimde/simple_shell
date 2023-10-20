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

void parse_command(char *command, char *args[MAX_ARGS])
{
	int i = 0;
	char *token = strtok(command, " \t\n");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i] = token;
		token = strtok(NULL, " \t\n");
		i++;
	}
	args[i] = NULL;
}

void execute_command(char *args[MAX_ARGS])
{
	pid_t pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("Simple_Shell");
			exit(1);
		}
	}
	else if (pid < 0)
	{
		perror("Simple_Shell");
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
	}
}

void add_alias(char *name, char *value)
{
	Alias *new_alias = (Alias *)malloc(sizeof(Alias));
	if (!new_alias)
	{
		perror("Simple_Shell");
		return;
	}
	new_alias->name = strdup(name);
	new_alias->value = strdup(value);
	new_alias->next = alias_list;
	alias_list = new_alias;
}

int resolve_alias(char *name, char *resolved, size_t size)
{
	Alias *alias = alias_list;
	while (alias)
	{
		if (strcmp(alias->name, name) == 0)
		{
			snprintf(resolved, size, "%s", alias->value);
			return (1);
		}
		alias = alias->next;
	}
	return (0);
}

void list_env_variables()
{
	extern char **environ;
	char **env = environ;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

int main(int argc, char *argv[])
{
	char input[MAX_INPUT_SIZE];
	char *args[MAX_ARGS];

	if (argc > 1)
	{
		FILE *file = fopen(argv[1], "r");
		if (file == NULL)
		{
			perror("Simple_Shell");
			exit(1);
		}

		while (fgets(input, sizeof(input), file) != NULL)
		{
			if (strlen(input) <= 1)
			{
				continue;
			}

			parse_command(input, args);
			execute_command(args);
		}

		fclose(file);
		exit(0);
	}

	while (1)
	{
		char resolved_command[MAX_INPUT_SIZE];
		int alias_resolved;

		printf("Simple_Shell> ");
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			exit(0);
		}

		if (strlen(input) <= 1)
		{
			continue;
		}

		input[strcspn(input, "\n")] = 0;

		if (input[0] == '#')
		{
			continue;
		}

		alias_resolved = resolve_alias(input, resolved_command, sizeof(resolved_command));
		if (alias_resolved)
		{
			printf("Resolved alias: %s\n", resolved_command);
			parse_command(resolved_command, args);
			execute_command(args);
		}
		else
		{
			parse_command(input, args);
			if (args[0] != NULL)
			{
				if (strcmp(args[0], "exit") == 0)
				{
					if (args[1] == NULL)
						exit(0);
					else
					{
						int status = atoi(args[1]);
						exit(status);
					}
				}
				else if (strcmp(args[0], "env") == 0)
				{
					list_env_variables();
				}
				else if (strcmp(args[0], "cd") == 0)
				{
					if (args[1] == NULL)
						fprintf(stderr, "Simple_Shell: cd: missing argument\n");
					else if (chdir(args[1]) != 0)
						perror("Simple_Shell");
				}
				else if (strcmp(args[0], "alias") == 0)
				{
					if (args[1] != NULL)
					{
						if (args[2] != NULL)
							add_alias(args[1], args[2]);
						else
						{
							Alias *alias = alias_list;
							while (alias)
							{
								printf("%s='%s'\n", alias->name, alias->value);
								alias = alias->next;
							}
						}
					}
				}
				else
				{
					execute_command(args);
				}
			}
		}
	}

	return (0);
}
