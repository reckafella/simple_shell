#include "main.h"

/**
 * check_chain_delims - find if current char in buffer is a chain delimeter
 * @data: struct
 * @buffer: the char buffer
 * @pos: address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int check_chain_delims(func_t *data, char *buffer, size_t *pos)
{
	size_t j = *pos;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		data->command_btype = COMMAND_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		data->command_btype = COMMAND_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0; /* replace the semicolon with null character */
		data->command_btype = COMMAND_CHAIN;
	}
	else
		return (0);
	*pos = j;
	return (1);
}

/**
 * continue_chains - whether to continue chaining based on previous status
 * @data: struct
 * @buffer: character buffer
 * @pos: address of current position in buffer
 * @start: starting position in buffer
 * @buflen: length of buffer
 *
 * Return: Void
 */
void continue_chains(func_t *data, char *buffer, size_t *pos, size_t start, size_t buflen)
{
	size_t j = *pos;

	if (data->command_btype == COMMAND_AND)
	{
		if (data->exe_stat)
		{
			buffer[start] = 0;
			j = buflen;
		}
	}
	if (data->command_btype == COMMAND_OR)
	{
		if (!data->exe_stat)
		{
			buffer[start] = 0;
			j = buflen;
		}
	}

	*pos = j;
}

/**
 * replace_alias_node - replaces an alias_node in the token string
 * @data: struct
 *
 * Return: 1 on success, 0 otherwise
 */
int replace_alias_node(func_t *data)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_matches_prefix(data->alias_node, data->agstr[0], '=');
		if (!node)
			return (0);
		free(data->agstr[0]);
		p = _strchr(node->string, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		data->agstr[0] = p;
	}
	return (1);
}

/**
 * replace_variables - replace variables in the token
 * @data: struct
 *
 * Return: 1 on success, 0 otherwise
 */
int replace_variables(func_t *data)
{
	int i = 0;
	list_t *node;

	for (i = 0; data->agstr[i]; i++)
	{
		if (data->agstr[i][0] != '$' || !data->agstr[i][1])
			continue;

		if (!_strcmp(data->agstr[i], "$?"))
		{
			replace_str(&(data->agstr[i]),
				_strdup(convert_num(data->exe_stat, 10, 0)));
			continue;
		}
		if (!_strcmp(data->agstr[i], "$$"))
		{
			replace_str(&(data->agstr[i]),
				_strdup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = node_matches_prefix(data->env, &data->agstr[i][1], '=');
		if (node)
		{
			replace_str(&(data->agstr[i]),
				_strdup(_strchr(node->string, '=') + 1));
			continue;
		}
		replace_str(&data->agstr[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_str - replace a string
 * @oldstr: old string's address
 * @newstr: new string's address
 *
 * Return: 1 on success, 0 otherwise
 */
int replace_str(char **oldstr, char *newstr)
{
	free(*oldstr);
	*oldstr = newstr;
	return (1);
}
