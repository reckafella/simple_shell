#include "main.h"

/**
 * _getenv - get the environment variable
 * @name: environmment variable name
 *
 * Return: pointer to the env variable
*/
char *_getenv(const char *name)
{
	char **ptr = environ;
	int len = _strlen(name);

	while (*ptr != NULL)
	{
		if (_strncmp(name, *ptr, len) == 0 && (*ptr)[len] == '=')
		{
			return (&((*ptr)[len + 1]));
		}
		ptr++;
	}
	return (NULL);
}

/**
 * print_env - print environment variable
*/
void print_env(void)
{
	char **s = environ;

	for (; *s; s++)
		dprintf(STDOUT_FILENO, "%s\n", *s);
}
