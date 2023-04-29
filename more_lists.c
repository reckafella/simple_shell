#include "main.h"

/**
 * list_length - returns length of a linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t list_length(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * list_arrays - returns an array of strings of the list->str
 * @h: first node
 *
 * Return: array of strings
 */
char **list_arrays(list_t *h)
{
	list_t *node = h;
	size_t i = list_length(h), j;
	char **strings;
	char *_str;

	if (!h || !i)
		return (NULL);
	strings = malloc(sizeof(char *) * (i + 1));
	if (!strings)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		_str = malloc(_strlen(node->string) + 1);
		if (!_str)
		{
			for (j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		_str = _strcpy(_str, node->string);
		strings[i] = _str;
	}
	strings[i] = NULL;
	return (strings);
}


/**
 * print_linked_list - prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_linked_list(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(convert_num(head->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->string ? head->string : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * node_matches_prefix - return node with string that starts with the prefix
 * @node: pointer to head of a linked list
 * @prefix: string being matched
 * @ch: the next character after prefix to match
 *
 * Return: matched node or null
 */
list_t *node_matches_prefix(list_t *node, char *prefix, char ch)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->string, prefix);
		if (ptr && ((ch == -1) || (*ptr == ch)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getnode_at_index - returns a node's index
 * @head: head of linked list
 * @node: node of linked list
 *
 * Return: index of node or -1
 */
ssize_t getnode_at_index(list_t *head, list_t *node)
{
	ssize_t index = 0;

	while (head)
	{
		if (node == head)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
