#include "main.h"

/**
 * change_directory - function to help navigate directories
*/

int change_directory(char *argv[])
{
	/**
	 * if argv[1] not provided go to home
	 * else if not existing, print an error and return -1
	*/

	if (argv[1] == NULL)
	{
		chdir(getenv("HOME"));
		return (1);
	}
	else
	{
		if (chdir(argv[1]) == -1)
		{
			printf("%s: No such file or directory\n", argv[1]);
			return (-1);
		}
	}

	return (0);
}
