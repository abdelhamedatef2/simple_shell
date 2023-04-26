#include "shell.h"
/**
 * clear_info - Clears all fields of an info_t struct
 * @info: Pointer to an info_t struct to be cleared
 *
 * Return: void
 */
void clear_info(info_t *info)
{
	/* Set all fields of info to NULL/0 */
	memset(info, 0, sizeof(info_t));
}
/**
 * set_info - Sets fields of an info_t struct using command line arguments
 * @info: Pointer to an info_t struct to be filled
 * @av: Array of command line arguments
 *
 * Return: void
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];

	if (info->arg)
	{
		/* Split argument string into array of arguments */
		info->argv = strtow(info->arg, " \t");

		/* If info->argv is NULL, allocate space for single argument */
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}

		/* Count the number of arguments */
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		/* Replace any aliases and variables in the arguments */
		replace_alias(info);
		replace_vars(info);
	}
}
/**
 * free_info - Frees memory used by an info_t struct
 * @info: Pointer to an info_t struct
 * @all: Flag indicating whether to free all memory
 *
 * Return: void
 */
void free_info(info_t *info, int all)
{
	/* Free info->argv and set to NULL */
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
		/* Free info->arg if cmd_buf is not set */
		if (!info->cmd_buf)
			free(info->arg);

		/* Free linked lists of environment, history, and aliases */
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));

		/* Free info->environ and set to NULL */
		ffree(info->environ);
		info->environ = NULL;

		/* Free info->cmd_buf and set to NULL */
		bfree((void **)info->cmd_buf);

		/* Close readfd if it's greater than 2 */
		if (info->readfd > 2)
			close(info->readfd);

		/* Flush output buffer */
		_putchar(BUF_FLUSH);
	}
}
