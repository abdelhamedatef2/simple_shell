#include "shell.h"
/**
 * _memset - fills the first n bytes of the memory area pointed to by s
 *           with the constant byte b
 * @s: a pointer to the memory area to be filled
 * @b: the value to be set
 * @n: the number of bytes to be set to the value
 *
 * Return: a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		s[i] = b;
	}

	return (s);
}
/**
 * ffree - frees a double pointer and all its contents
 * @pp: a double pointer to be freed
 */
void ffree(char **pp)
{
	if (!pp)
		return;

	char **p = pp;

	while (*p)
	{
		free(*p);
		p++;
	}

	free(pp);
}
/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: a pointer to the memory previously allocated
 * @old_size: the size of the allocated space for ptr
 * @new_size: the new size to be allocated
 *
 * Return: a pointer to the newly allocated memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	return (p);
}
