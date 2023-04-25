#include "shell.h"
/**
 * _strcpy - Copies a string from source to destination.
 *
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to destination string.
 */

char *_strcpy(char *dest, const char *src)
{
	if (dest == src || src == NULL){
		return (dest);

	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';

	return (dest);
}
/**
 * _strdup - Returns a pointer to a newly allocated space in memory,
 * containing a copy of the string given as parameter.
 *
 * @str: Pointer to the string to be duplicated.
 *
 * Return: Pointer to the duplicated string.
 */

char *_strdup(const char *str)
{
	if (str == NULL)
		return (NULL);

	size_t length = strlen(str);
	char *ret = malloc((length + 1) * sizeof(char));

	if (ret == NULL)
		return (NULL);

	strcpy(ret, str);

	return (ret);
}
/**
 * _puts - Prints a string to stdout.
 *
 * @str: Pointer to the string to be printed.
 *
 * Return: void
 */

void _puts(char *str)
{
	if (str == NULL)
		return;

	for (size_t i = 0; str[i] != '\0'; i++)
	{
		_putchar(str[i]);
	}
}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
