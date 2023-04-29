#include "main.h"

/**
 * read_line - input string reading.
 *
 * @i_eof: value of getline
 * Return: the str has inputed
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
