#include "main.h"

/**
 * input_buffer - buffers chained commands
 * @data: parameter struct
 * @buffer: address of buffer
 * @length: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buffer(func_t *data, char **buffer, size_t *length)
{
	ssize_t bytes_read = 0;
	size_t len_p = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigint_handler);
#if USE_GETLINE
		bytes_read = getline(buf, &len_p, stdin);
#else
		bytes_read = _getline(data, buffer, &len_p);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			data->lc_flag = 1;
			remove_comments(*buffer);
			build_history_list(data, *buffer, data->hist_cnt++);
			{
				*length = bytes_read;
				data->command_buffer = buffer;
			}
		}
	}
	return (bytes_read);
}

/**
 * getline_input - gets a line minus the newline
 * @data: struct
 *
 * Return: bytes read
 */
ssize_t getline_input(func_t *data)
{
	static char *buffer;
	static size_t itr, j, length;
	ssize_t bytes_read = 0;
	char **buf_p = &(data->getline_arg), *ptr;

	_putchar(BUFFER_FLUSH);
	bytes_read = input_buffer(data, &buffer, &length);
	if (bytes_read == -1) /* reached EOF */
		return (-1);
	if (length)
	{
		j = itr;
		ptr = buffer + itr;

		continue_chains(data, buffer, &j, itr, length);
		while (j < length)
		{
			if (check_chain_delims(data, buffer, &j))
				break;
			j++;
		}

		itr = j + 1;
		if (itr >= length)
		{
			itr = length = 0;
			data->command_btype = COMMAND_NORM;
		}

		*buf_p = ptr;
		return (_strlen(ptr));
	}

	*buf_p = buffer;
	return (bytes_read);
}

/**
 * read_buffer - reads a buffer
 * @data: struct
 * @buffer: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buffer(func_t *data, char *buffer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(data->rfd, buffer, READ_BUFFER_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @data: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(func_t *data, char **ptr, size_t *length)
{
	static char buf[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buffer(data, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = reallocate_memory(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigint_handler - blocks ctrl-C
 * @sig_num: the signal number
 */
void sigint_handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}
