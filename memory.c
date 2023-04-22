#iclude "shell.h"
/**
 * bfree - Frees a memory block and sets its pointer to NULL
 * @ptr: Pointer to the memory block to free
 *
 * Return: 1 if memory was freed, 0 if not
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	else
	{
		return (0);
	}
}
