#include "main.h"

/**
 * main - the main method of the shell program
 * @argc: number of arguments
 * @argv: no
 * @envp: no
 *
 * Return: 0
*/

int main(int argc, char *argv[], char **envp)
{
	char line[MAX_LINE];
	char *tokens[LIMIT];
	int num_of_tokens;

	/* This prevents the printing of the shell after certain methods */
	no_reprint_prmpt = 0;

	/* Initialize pid with an impossible value */
	pid = -10;

	/* Initalize the shell program */
	initialize_shell();
	welcome_screen();

	/* Our loop within which input is read and output printed */
	while (TRUE)
	{
		/* print shell prompt if necessary*/
		if (no_reprint_prmpt == 0)
			shell_prompt();
		no_reprint_prmpt = 0;

		/* Empty line buffer */
		memset(line, '\0', MAX_LINE);

		/* wait for user input */
		fgets(line, MAX_LINE, stdin);

		/* When no input is passed, loop is re-executed */
		tokens[0] = strtok(line, " \n\t");
		if ((tokens[0]) == NULL)
			continue;

		/* read all tokens of the input and pass it to command_handler */
		num_of_tokens = 1;
		while ((tokens[num_of_tokens] = strtok(NULL, " \n\t")) != NULL)
			num_of_tokens++;
		command_handler(tokens);
	}
	exit(0);
}
