#include "main.h"

/**
 * execute_command - execute commands
 * @argv: argument vector
 * @command: pointer to command
*/
void execute_command(char **argv, char *command)
{
	char *tokens[MAX_COMMANDS], *token;
	int arg_count = 0, status;
	pid_t child_pid;

	token = strtok(command, " ");
	while (token != NULL)
	{
		tokens[arg_count] = token;
		arg_count++;
		token = strtok(NULL, " ");
	}
	tokens[arg_count] = NULL;

	child_pid = fork();
	if (child_pid == -1)
	{
		free(command);
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		/* handle builtins */
		if (_strcmp(tokens[0], "cd") == 0)
			change_directory(tokens);
		else
		{
			if (execve(tokens[0], tokens, environ) == -1)
			{
				fprintf(stderr, "%s: Command not found\n", argv[0]);
				free(command);
				exit(EXIT_SUCCESS);
			}
		}
	}
	else
		wait(&status);
}
