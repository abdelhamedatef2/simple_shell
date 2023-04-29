#include "main.h"

/**
 * read_line - reads str
 *
 * @i_eof: vlaue of get_line
 * Return: str
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
