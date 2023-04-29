#include "main.h"

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}


/**
 * _strcmp - compare two strings
 * @first: first string
 * @second: second string
 *
 * Return: 0 if (s1 == s2), <0 if (s1 < s2), >0 if (s2 > s1)
*/
int _strcmp(const char *first, const char *second)
{
	while (*first && *second)
	{
		if (*first != *second)
			return (*first - *second);
		first++;
		second++;
	}
	if (*first == *second)
		return (0);
	else
		return (*first < *second ? -1 : 1);
}

/**
 * starts_with - does needle found at start of haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack / NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
