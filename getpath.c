#include "main.h"

/**
 * getpath - returns full path to an executable command
 * @command: command args
 *
 * Return: pointer to the address of full_path
*/
char *getpath(char *command)
{
	char *path, *path_copy, *dir_path, *full_path = NULL;
	int command_len, path_len, full_path_len;

	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
			return (command);
	}
	else
	{
		path = _getenv("PATH");
		if (path != NULL)
		{
			path_copy = _strdup(path); /* create a copy of PATH */
			if (path_copy == NULL)
				return (NULL);
			dir_path = strtok(path_copy, ":");
			while (dir_path != NULL)
			{
				command_len = _strlen(command), path_len = _strlen(dir_path);
				full_path_len = (command_len + path_len + 2);
				full_path = malloc(full_path_len * sizeof(char));
				if (full_path == NULL)
				{
					free(path_copy);
					return (NULL);
				}
				snprintf(full_path, full_path_len, "%s/%s", dir_path, command);
				if (access(full_path, X_OK) == 0)
				{
					free(path_copy); /* free the copy of PATH */
					return (full_path);
				}
				free(full_path);
				full_path = NULL, dir_path = strtok(NULL, ":");
			}
			free(path_copy); /* free the copy of PATH */
		}
	}
	return (NULL);
}
