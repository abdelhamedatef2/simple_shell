#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t bytes_read = 0;
	size_t len_p = 0;

	if (*len == 0)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytes_read = getline(buf, &len_p, stdin);
#else
		bytes_read = _getline(info, buf, &len_p);
#endif
		if (bytes_read > 0)
		{
			if ((*buf)[bytes_read - 1] == '\n')
			{
				(*buf)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			if (strchr(*buf, ';') != NULL)
			{
				*len = bytes_read;
				info->cmd_buf = buf;
			}
		}
	}

	return (bytes_read);
}
/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, len;
	ssize_t bytes_read = 0;
	char **buf_p = &(info->arg);

	_putchar(BUF_FLUSH);
	bytes_read = input_buf(info, &buf, &len);

	if (bytes_read == -1) /* EOF */
		return (-1);
	if (len > 0)
	{
		size_t j = i;
		char *p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (strlen(p));
	}

	*buf_p = buf;
	return (bytes_read);
}
/**
 * read_buf - read data from a file descriptor into a buffer.
 * @info: pointer to a struct containing information about the file descriptor.
 * @buf: pointer to a buffer to hold the data read from the file descriptor.
 * @i: pointer to a size_t variable
 * that will be set to the number of bytes read.
 *
 * Return: the number of bytes read on success, or -1 on error.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	if (*i > 0)
	{
		return (0);
	}

	ssize_t num_bytes_read = read(info->readfd, buf, READ_BUF_SIZE);

	if (num_bytes_read < 0)
	{
		return (num_bytes_read);
	}

	*i = num_bytes_read;
	return (num_bytes_read);
}
/**
 * _getline - read a line of text from a file descriptor.
 * @info: pointer to a struct containing information about the file descriptor.
 * @ptr: pointer to a pointer to a buffer to store the line of text.
 * @length: pointer to a variable to store the length of the buffer.
 *
 * Return: the number of bytes read on success, or -1 on failure.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	ssize_t num_bytes_read = 0;
	size_t k = 0;
	char *p = NULL, *new_p = NULL, *c = NULL;

	p = *ptr;
	if (p && length)
		num_bytes_read = *length;
	if (i == len)
		i = len = 0;

	num_bytes_read = read_buf(info, buf, &len);
	if (num_bytes_read == -1 || (num_bytes_read == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, num_bytes_read, p ? num_bytes_read + k : k + 1);
	if (!new_p)
	{
		if (p)
			free(p);
		return (-1);
	}

	if (num_bytes_read)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	num_bytes_read += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = num_bytes_read;
	*ptr = p;
	return (num_bytes_read);
}
/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

