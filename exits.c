#include "shell.h"

/**
 **_strncpy - copies a string
 *@destination: the destination string to be copied to
 *@source: the source string
 *@num_chars: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *destination, const char *source, int num_chars)
{
	int index1, index2;
	char *start = destination;

	index1 = 0;
	while (source[index1] != '\0' && index1 < num_chars - 1)
	{
		destination[index1] = source[index1];
		index1++;
	}
	if (index1 < num_chars)
	{
		index2 = index1;
		while (index2 < num_chars)
		{
			destination[index2] = '\0';
			index2++;
		}
	}
	return (start);
}
/**
 **_strncat - concatenates two strings
 *@destination: the first string
 *@source: the second string
 *@max_bytes: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *destination, const char *source, int max_bytes)
{
	int index1, index2;
	char *start = destination;

	index1 = 0;
	while (destination[index1] != '\0')
	{
		index1++;
	}
	index2 = 0;
	while (source[index2] != '\0' && index2 < max_bytes)
	{
		destination[index1] = source[index2];
		index1++;
		index2++;
	}
	if (index2 < max_bytes)
	{
		destination[index1] = '\0';
	}
	return (start);
}
/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
