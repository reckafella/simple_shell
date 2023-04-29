#include "main.h"

/**
 * shell_env - print the current environment
 * @data: Structfor maintaining constant function prototype.
 *
 * Return: Always 0
 */
int shell_env(func_t *data)
{
	print_list_str(data->env);
	return (0);
}


/**
 * _getenv - get the value of an environ variable
 * @data: Struct used to maintain constant function prototypes
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(func_t *data, const char *name)
{
	list_t *node = data->env;
	char *p;

	while (node)
	{
		p = starts_with(node->string, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}


/**
 * set_env - Initialize a new environment variable, or modify an existing one
 * @data: Structure used to maintain constant function prototype.
 *
 *  Return: Always 0
 */
int set_env(func_t *data)
{
	if (data->ac != 3)
	{
		_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(data, data->agstr[1], data->agstr[2]))
		return (0);
	return (1);
}


/**
 * unset_env - Remove an environment variable
 * @data: Structure used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int unset_env(func_t *data)
{
	int i;

	if (data->ac == 1)
	{
		_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= data->ac; i++)
		_unsetenv(data, data->agstr[i]);

	return (0);
}


/**
 * append_env_list - populates env linked list
 * @data: Structure used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int append_env_list(func_t *data)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	data->env = node;
	return (0);
}
