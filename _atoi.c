#include "shell.h"

/**
 * is_interactive_mode - checks if shell is in interactive mode
 * @info: a pointer to a struct containing shell information
 *
 * Return: 1 if shell is in interactive mode, 0 otherwise
 */
int is_interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= STDERR_FILENO);
}

/**
 * is_delimiter - checks if a character is a delimiter
 * @c: the character to check
 * @delimiters: a string containing delimiter characters
 *
 * Return: 1 if c is a delimiter, 0 otherwise
 */
int is_delimiter(char c, char *delimiters)
{
	while (*delimiters)
		if (*delimiters++ == c)
			return (1);
	return (0);
}

/**
 * is_alphabetic - checks if a character is alphabetic
 * @c: the character to check
 *
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int is_alphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * string_to_integer - converts a string to an integer
 * @str: the string to convert
 *
 * Return: the converted integer, or 0 if no numbers found in string
 */
int string_to_integer(char *str)
{
	int i, sign = 1, state = 0, output;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && state != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			state = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (state == 1)
			state = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
