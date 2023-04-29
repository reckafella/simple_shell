#include "main.h"

/**
 * hist_list - prints the history, one command on each line, preceded.
 * @data: Structure with args. For maintaining
 *        function prototypes.
 *  Return: 0 Always
 */
int hist_list(func_t *data)
{
	print_linked_list(data->hist);
	return (0);
}

/**
 * unset_alias_node - sets alias_node to string
 * @data: parameter struct
 * @str: the string alias_node
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias_node(func_t *data, char *string)
{
	char *ptr, ch;
	int result;

	ptr = _strchr(string, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	result = delete_node_at_index(&(data->alias_node),
		getnode_at_index(data->alias_node, node_matches_prefix(data->alias_node, string, -1)));
	*ptr = ch;
	return (result);
}

/**
 * set_alias_node - sets alias_node to string
 * @data: parameter struct
 * @str: the string alias_node
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias_node(func_t *data, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias_node(data, str));

	unset_alias_node(data, str);
	return (add_node_end(&(data->alias_node), str, 0) == NULL);
}

/**
 * print_alias_node - prints an alias_node string
 * @node: the alias_node node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias_node(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->string, '=');
		for (a = node->string; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_node - the alias_node builtin
 * @data: Structure.
 *  Return: Always 0
 */
int alias_node(func_t *data)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (data->ac == 1)
	{
		node = data->alias_node;
		while (node)
		{
			print_alias_node(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->agstr[i]; i++)
	{
		p = _strchr(data->agstr[i], '=');
		if (p)
			set_alias_node(data, data->agstr[i]);
		else
			print_alias_node(node_matches_prefix(data->alias_node, data->agstr[i], '='));
	}

	return (0);
}
