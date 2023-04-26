#include "shell.h"

/**
 * _strlen - Computes the length of a string.
 * @s: A pointer to a string.
 *
 * Return: The length of the string.
 */
int _strlen(char *s)
{
	if (s == NULL)
		return (0);

	char *p = s;

	while (*p)
		p++;

	return (p - s);
}
/**
 * _strcmp - Compares two strings.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 *
 * Return: An integer less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, to match, or be greater than s2.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
/**
 * starts_with - Checks if a string starts with a given prefix.
 * @haystack: The string to search in.
 * @needle: The prefix to search for.
 *
 * Return: A pointer to the start of the suffix in haystack if it starts with
 * the prefix needle, otherwise NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle != '\0')
	{
		if (*haystack != *needle)
			return (NULL);
		haystack++;
		needle++;
	}
	return ((char *)haystack);
}
/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: A pointer to the destination string.
 */
char *_strcat(char *dest, char *src)
{
	char *p = dest;

	while (*p)
	{
		p++;
	}
	while (*src)
		*p++ = *src++;
	*p = '\0';

	return (dest);
}
