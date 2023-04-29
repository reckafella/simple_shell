#include "main.h"

/**
 * _strcpy - copies a string
 * @dst: destination
 * @src: source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dst, char *src)
{
	int i = 0;

	if (dst == src || src == 0)
		return (dst);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

/**
 *_puts - print a string
 *@str: the string
 */
void _puts(char *str)
{
	int i = 0;

	if (str == NULL)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
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
 * _strdup - return a pointer to a duplicate of given string parameter
 * @str: input string parameter
 *
 * Return: pointer
 */

char *_strdup(const char *str)
{
	int len = 0;
	int i = 0;

	char *ptr;

	if (!str)
		return (NULL);

	while (str[len] != '\0')
		++len;

	ptr = malloc((len + 1) * sizeof(char));

	if (!ptr)
		return (NULL);

	while (str[i] != '\0')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';

	return (ptr);
}
