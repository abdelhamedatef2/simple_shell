#include "shell.h"

/**
 * _eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	if (str == NULL)
		return;

	for (; *str != '\0'; str++)
		_eputchar(*str);
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, return -1, and error is set appropriately.
 */
int _eputchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (i == WRITE_BUF_SIZE)
	{
		if (write(2, buf, i) == -1)
			return (-1);
		i = 0;
	}

	buf[i++] = c;

	if (c == BUF_FLUSH || i == WRITE_BUF_SIZE)
	{
		if (write(2, buf, i) == -1)
			return (-1);
		i = 0;
	}

	return (1);
}
/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (i == WRITE_BUF_SIZE || c == BUF_FLUSH)
	{
		ssize_t bytes_written = write(fd, buf, i);

		if (bytes_written == -1)
			return (-1);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}
/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	if (str == NULL)
		return (0);

	int count = 0;

	for (; *str != '\0'; str++)
	{
		if (_putfd(*str, fd) == -1)
			return (-1);
		count++;
	}

	return (count);
}
