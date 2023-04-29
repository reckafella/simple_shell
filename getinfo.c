#include "main.h"

/**
 * clear_data - initializes func_t struct
 * @data: struct address
 */
void clear_data(func_t *data)
{
	data->getline_arg = NULL;
	data->agstr = NULL;
	data->command_path = NULL;
	data->ac = 0;
}

/**
 * set_data - initializes func_t struct
 * @data: struct address
 * @av: argument vector
 */
void set_data(func_t *data, char **av)
{
	int i = 0;

	data->filename = av[0];
	if (data->getline_arg)
	{
		data->agstr = strtwd(data->getline_arg, " \t");
		if (!data->agstr)
		{

			data->agstr = malloc(sizeof(char *) * 2);
			if (data->agstr)
			{
				data->agstr[0] = _strdup(data->getline_arg);
				data->agstr[1] = NULL;
			}
		}
		for (i = 0; data->agstr && data->agstr[i]; i++)
			;
		data->ac = i;

		replace_alias_node(data);
		replace_variables(data);
	}
}

/**
 * free_data - frees func_t struct fields
 * @data: struct address
 * @all: true if freeing all fields
 */
void free_data(func_t *data, int all)
{
	ffree(data->agstr);
	data->agstr = NULL;
	data->command_path = NULL;
	if (all)
	{
		if (!data->command_buffer)
			free(data->getline_arg);
		if (data->env)
			free_list(&(data->env));
		if (data->hist)
			free_list(&(data->hist));
		if (data->alias_node)
			free_list(&(data->alias_node));
		ffree(data->environ);
			data->environ = NULL;
		bfree((void **)data->command_buffer);
		if (data->rfd > 2)
			close(data->rfd);
		_putchar(BUFFER_FLUSH);
	}
}
