#include "main.h"

/**
 * check_if_interactive - returns true if shell is interactive mode
 * @data: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int check_if_interactive(func_t *data)
{
	return (isatty(STDIN_FILENO) && data->rfd <= 2);
}

/**
 * check_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int check_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *check_alpha - determine alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int check_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - convert a string to int
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
