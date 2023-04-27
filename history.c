#include "main.h"
/**
 * read_history - reads history from .hsh_history file
*/
void read_history(void)
{
	char history_file[1000];
	char command[1000];
	int count = 0;
	FILE *fp = NULL;

	sprintf(history_file, "%s/%s", _getenv("HOME"), HISTORY_FILE);

	fp = fopen(history_file, "r");
	if (fp == NULL)
	{
		perror("Error opening history file");
		return;
	}

	while (fgets(command, sizeof(command), fp) != NULL)
	{
		dprintf(STDOUT_FILENO, "%d %s", count, command);
		count++;
	}

	fclose(fp);
}

/**
 * append_history - adds history as commands are executed
 * @command: buffer containing command
*/
void append_history(char *command)
{
	char history_file[1000];
	FILE *fp = NULL;

	sprintf(history_file, "%s/%s", getenv("HOME"), HISTORY_FILE);
	fp = fopen(history_file, "a");
	if (fp == NULL)
	{
		perror("Error opening history file");
		return;
	}

	fprintf(fp, "%s\n", command);

	fclose(fp);
}

