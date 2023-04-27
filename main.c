#include "main.h"

/**
 * main - program's entry point
 * @argc: number of args
 * @argv: vector of args
 *
 * Return: 0 always
*/
int main(int argc, char **argv)
{
	if (argc >= 1)
		prompt(argv);

	return (0);
}

/**
 * prompt - provides prompt for user to enter commands
 * @argv: commands
*/
void prompt(char **argv)
{
	char *buffer = NULL;
	size_t n = 0;
	ssize_t char_count;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		char_count = getline(&buffer, &n, stdin);
		if (char_count == -1)
		{
			free(buffer);
			exit(EXIT_FAILURE);
		}
		buffer[strcspn(buffer, "\n")] = 0;

		if (_strcmp(buffer, "exit") == 0)
		{
			cleanup(buffer);
			exit(EXIT_SUCCESS);
		}
		else if (_strcmp(buffer, "help") == 0)
			dprintf(STDOUT_FILENO, "%s\n", SHELL_HELP);
		else if (_strcmp(buffer, "env") == 0)
			print_env();
		else if (_strcmp(buffer, "history") == 0)
			read_history();
		else
		{
			execute_command(argv, buffer);
			append_history(buffer);
		}
	}
	free(buffer);
}
