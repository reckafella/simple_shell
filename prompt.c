#include "main.h"

/**
 * prompt - main shell loop
 * @data: the parameter & return data struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int prompt(func_t *data, char **argv)
{
	ssize_t bytes_read = 0;
	int blt_ret = 0;

	while (bytes_read != -1 && blt_ret != -2)
	{
		clear_data(data);
		if (check_if_interactive(data))
			_puts("$ ");
		print_echar(BUFFER_FLUSH);
		bytes_read = getline_input(data);
		if (bytes_read != -1)
		{
			set_data(data, argv);
			blt_ret = handle_builtins(data);
			if (blt_ret == -1)
				find_command(data);
		}
		else if (check_if_interactive(data))
			_putchar('\n');
		free_data(data, 0);
	}
	write_history(data);
	free_data(data, 1);
	if (!check_if_interactive(data) && data->exe_stat)
		exit(data->exe_stat);
	if (blt_ret == -2)
	{
		if (data->er_num == -1)
			exit(data->exe_stat);
		exit(data->er_num);
	}
	return (blt_ret);
}

/**
 * handle_builtins - finds a builtin command
 * @data: the parameter & return data struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int handle_builtins(func_t *data)
{
	int i, built_in_ret = -1;
	builtins_t builtin_s[] = {
		{"exit", exit_shell},
		{"env", shell_env},
		{"help", shell_help},
		{"history", hist_list},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"cd", change_directory},
		{"alias_node", alias_node},
		{NULL, NULL}
	};

	for (i = 0; builtin_s[i].s_type; i++)
		if (_strcmp(data->agstr[0], builtin_s[i].s_type) == 0)
		{
			data->err_count++;
			built_in_ret = builtin_s[i].fun(data);
			break;
		}
	return (built_in_ret);
}

/**
 * find_command - finds a command in PATH
 * @data: the parameter & return data struct
 *
 * Return: void
 */
void find_command(func_t *data)
{
	char *path = NULL;
	int i, k;

	data->command_path = data->agstr[0];
	if (data->lc_flag == 1)
	{
		data->err_count++;
		data->lc_flag = 0;
	}
	for (i = 0, k = 0; data->getline_arg[i]; i++)
		if (!check_delim(data->getline_arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = _find_full_path(data, _getenv(data, "PATH="), data->agstr[0]);
	if (path)
	{
		data->command_path = path;
		fork_command(data);
	}
	else
	{
		if ((check_if_interactive(data) || _getenv(data, "PATH=")
			|| data->agstr[0][0] == '/') && valid_command(data, data->agstr[0]))
			fork_command(data);
		else if (*(data->getline_arg) != '\n')
		{
			data->exe_stat = 127;
			print_error(data, "not found\n");
		}
	}
}

/**
 * fork_command - forks an exec thread to run cmd
 * @data: the parameter & return data struct
 */
void fork_command(func_t *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->command_path, data->agstr, get_environ(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(data->exe_stat));
		if (WIFEXITED(data->exe_stat))
		{
			data->exe_stat = WEXITSTATUS(data->exe_stat);
			if (data->exe_stat == 126)
				print_error(data, "Permission denied\n");
		}
	}
}
