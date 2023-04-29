#include "main.h"

/**
 * get_environ - returns the string array copy of our environ
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(func_t *data)
{
	if (!data->environ || data->env_status)
	{
		data->environ = list_arrays(data->env);
		data->env_status = 0;
	}

	return (data->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(func_t *data, char *var)
{
	list_t *node = data->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->string, var);
		if (p && *p == '=')
		{
			data->env_status = delete_node_at_index(&(data->env), i);
			i = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (data->env_status);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(func_t *data, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = data->env;
	while (node)
	{
		p = starts_with(node->string, var);
		if (p && *p == '=')
		{
			free(node->string);
			node->string = buf;
			data->env_status = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(data->env), buf, 0);
	free(buf);
	data->env_status = 1;
	return (0);
}
