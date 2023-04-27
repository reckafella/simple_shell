#include "main.h"

/**
 * _strlen - return string length
 * @str: null-terminated string
 *
 * Return: string length
*/
int _strlen(const char *str)
{
	int len = 0;

	while (str[len] != '\0')
		len++;

	return (len);
}

/**
 * _strncmp - compare two strings upto a specified position
 * @first: first string
 * @second: second string
 * @len: length
 *
 * Return: 0 if (s1 == s2), <0 if (s1 < s2), >0 if (s2 > s1)
*/
int _strncmp(const char *first, const char *second, size_t len)
{
	while (len && *first && (*first == *second))
	{
		first++;
		second++;
		len--;
	}

	if (len == 0)
		return (0);

	return (*(unsigned char *)first - *(unsigned char *)second);
}

/**
 * _strcmp - compare two strings upto a specified position
 * @first: first string
 * @second: second string
 *
 * Return: 0 if (s1 == s2), <0 if (s1 < s2), >0 if (s2 > s1)
*/
int _strcmp(const char *first, const char *second)
{
	while (*first && (*first == *second))
	{
		first++;
		second++;
	}
	return (*(unsigned char *)first - *(unsigned char *)second);
}

/**
 * _strtok - return tokens from slicing a string by a delimiter
 * @str: string
 * @delim: delimiter
 *
 * Return: pointer to the tokens
*/
char *_strtok(char *str, const char *delim)
{
	static char *last_str;
	char *start, *end;

	if (str != NULL)
		last_str = str;
	else if (last_str == NULL)
		return (NULL);

	start = last_str;
	while (*last_str != '\0')
	{
		end = last_str;

		while (*delim != '\0' && *delim != *last_str)
			delim++;
		if (*delim != '\0' && *last_str == *delim)
		{
			*last_str = '\0';
			last_str++;
			return (start);
		}
		last_str++;
		delim = delim - (end - last_str);
	}
	return (start);
}

/**
 * _strdup - return a pointer to a duplicate of given string parameter
 * @str: input string parameter
 *
 * Return: pointer
 */

char *_strdup(char *str)
{
	int len = 0;
	int i = 0;

	char *ptr;

	if (!str)
	{
		return (NULL);
	}

	while (str[len] != '\0')
	{
		++len;
	}

	ptr = malloc((len + 1) * sizeof(char));

	if (!ptr)
	{
		return (NULL);
	}

	while (str[i] != '\0')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';

	return (ptr);
}
