#include "shell.h"

/**
 * _erratoi - Converts a string to an integer.
 *
 * @s: The string to be converted.
 *
 * Return: 0 if no numbers in string, converted number otherwise, -1 on error.
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
	{
		s++;
	}

	for (i = 0; s[i] != '\0'; i++)
	{
		if (isdigit(s[i]))
		{
			result *= 10;
			result += (s[i] - '0');

			if (result > INT_MAX)
			{
				return (-1);
			}
		}
		else
		{
			return (-1);
		}
	}

	return (result);
}

/**
 * print_error - Prints an error message.
 *
 * @info: The parameter & return info struct.
 * @estr: String containing specified error type.
 *
 * Return: void
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Function prints a decimal int number (base 10).
 *
 * @input: The input.
 * @fd: The filedescriptor.
 *
 * Return: Number of characters printed.
 */
int print_d(int input, int fd)
{
	int (*putchar_func)(char) = _putchar;
	int i, count = 0;
	unsigned int abs_value, current;

	if (fd == STDERR_FILENO)
	{
		putchar_func = _eputchar;
	}

	if (input < 0)
	{
		abs_value = -input;
		putchar_func('-');
		count++;
	}
	else
	{
		abs_value = input;
	}

	current = abs_value;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_value / i)
		{
			putchar_func('0' + current / i);
			count++;
		}

		current %= i;
	}

	putchar_func('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Converter function, a clone of itoa.
 *
 * @num: Number.
 * @base: Base.
 * @flags: Argument flags.
 *
 * Return: String.
 */
char *convert_number(long int num, int base, int flags)
{
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = (num < 0 && !(flags & CONVERT_UNSIGNED)) ? -num : num;
	const char *array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";

	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (num < 0 && !(flags & CONVERT_UNSIGNED))
	{
		sign = '-';
	}

	if (sign)
	{
		*--ptr = sign;
	}

	return (ptr);
}

/**
 * remove_comments - Function replaces  '#' with '\0'.
 *
 * @buf: string Address to modify.
 *
 * Return: void
 */
void remove_comments(char *buf)
{
	char *hash_pos = strchr(buf, '#');

	if (hash_pos != NULL && (hash_pos == buf || *(hash_pos - 1) == ' '))
	{
		*hash_pos = '\0';
	}
}
