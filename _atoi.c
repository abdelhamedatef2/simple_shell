#include "shell.h"

/**
 * interactive - Determines if the shell is in interactive mode
 * @info: Pointer to info_t struct
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	if (isatty(STDIN_FILENO) && info->readfd <= 2)
		return (1);
	else
		return (0);
}
/**
 * is_delim - Checks if a character is a delimiter
 * @c: Character to check
 * @delim: Delimiter string
 *
 * Return: 1 if character is a delimiter, 0 otherwise
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}
/**
 * _isalpha - Checks if a character is an alphabetic character
 * @c: Character to check
 *
 * Return: 1 if character is an alphabetic character, 0 otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * _atoi - Converts a string to an integer
 * @str: String to convert
 *
 * Return: Integer representation of the string, or 0 if no numbers in string
 */
int _atoi(char *str)
{
	int sign = 1;
	unsigned int result = 0;

	/* Check for a negative sign */
	if (*str == '-')
	{
		sign = -1;
		str++;
	}

	/* Parse digits until a non-digit character is found */
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}

	/* Apply sign to result and return */
	return (sign * (int)result);
}
