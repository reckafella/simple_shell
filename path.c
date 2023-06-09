#include "main.h"

/**
 * valid_command - determines if a file is an executable command
 * @data: the data struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int valid_command(func_t *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _charsdup - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *_charsdup(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buffer[k++] = pathstr[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * _find_full_path - finds this cmd in the PATH string
 * @data: the data struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *_find_full_path(func_t *data, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (valid_command(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = _charsdup(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (valid_command(data, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
