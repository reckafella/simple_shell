#include "main.h"

/**
 * **strtwd - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @delim: the delimeter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtwd(char *str, char *delim)
{
	int i, j, k, m, tokens = 0;
	char **ptr;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!check_delim(str[i], delim) &&
				(check_delim(str[i + 1], delim) || !str[i + 1]))
			tokens++;

	if (tokens == 0)
		return (NULL);
	ptr = malloc((1 + tokens) * sizeof(char *));
	if (!ptr)
		return (NULL);
	for (i = 0, j = 0; j < tokens; j++)
	{
		while (check_delim(str[i], delim))
			i++;
		k = 0;
		while (!check_delim(str[i + k], delim) && str[i + k])
			k++;
		ptr[j] = malloc((k + 1) * sizeof(char));
		if (!ptr[j])
		{
			for (k = 0; k < j; k++)
				free(ptr[k]);
			free(ptr);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			ptr[j][m] = str[i++];
		ptr[j][m] = 0;
	}
	ptr[j] = NULL;
	return (ptr);
}

/**
 * **strtwd2 - split a string into tokens
 * @str: string
 * @delim: delimeter
 *
 * Return: a pointer to an array of strings / NULL
 */
char **strtwd2(char *str, char delim)
{
	int i, j, k, m, tokens = 0;
	char **ptr;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) ||
		    (str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
			tokens++;
	if (tokens == 0)
		return (NULL);
	ptr = malloc((1 + tokens) * sizeof(char *));
	if (!ptr)
		return (NULL);
	for (i = 0, j = 0; j < tokens; j++)
	{
		while (str[i] == delim && str[i] != delim)
			i++;
		k = 0;
		while (str[i + k] != delim && str[i + k] && str[i + k] != delim)
			k++;
		ptr[j] = malloc((k + 1) * sizeof(char));
		if (!ptr[j])
		{
			for (k = 0; k < j; k++)
				free(ptr[k]);
			free(ptr);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			ptr[j][m] = str[i++];
		ptr[j][m] = 0;
	}
	ptr[j] = NULL;
	return (ptr);
}
