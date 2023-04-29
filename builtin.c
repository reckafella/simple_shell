#include "main.h"

/**
 * exit_shell - exits the shell
 * @data: Structure containing arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: exits with a given exit status
 *         (0) if data.argv[0] != "exit"
 */
int exit_shell(func_t *data)
{
	int exit_check;

	if (data->agstr[1])
	{
		exit_check = _erratoi(data->agstr[1]);
		if (exit_check == -1)
		{
			data->exe_stat = 2;
			print_error(data, "Illegal number: ");
			_eputs(data->agstr[1]);
			print_echar('\n');
			return (1);
		}
		data->er_num = _erratoi(data->agstr[1]);
		return (-2);
	}
	data->er_num = -1;
	return (-2);
}

/**
 * change_directory - changes the current directory of the process
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int change_directory(func_t *data)
{
	char *s = getcwd(buffer, 1024), *dir, buffer[1024];
	int chdir_ret;

	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!data->agstr[1])
	{
		dir = _getenv(data, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(data, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(data->agstr[1], "-") == 0)
	{
		if (!_getenv(data, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(data, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = _getenv(data, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(data->agstr[1]);
	if (chdir_ret == -1)
	{
		print_error(data, "can't cd to ");
		_puts(data->agstr[1]);
		print_echar('\n');
	}
	else
	{
		_setenv(data, "OLDPWD", _getenv(data, "PWD="));
		_setenv(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * shell_help - changes the current directory of the process
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int shell_help(func_t *data)
{
	char **arg_array;

	arg_array = data->agstr;
	_puts("Function not implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
