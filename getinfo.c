#include "shell.h"
void clear_info(info_t *info)
{
	memset(info, 0, sizeof(info_t));
}

void set_info(info_t *info, char **av)
{
	info->fname = av[0];

	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (info->argv == NULL)
		{
			info->argv = malloc(2 * sizeof(char *));
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		info->argc = 0;
		if (info->argv)
		{
			for (int i = 0; info->argv[i]; i++)
				info->argc++;
			replace_alias(info);
			replace_vars(info);
		}
	}
}

void free_info(info_t *info, int all)
{
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		free_list(&(info->env));
		free_list(&(info->history));
		free_list(&(info->alias));
		bfree((void **)info->cmd_buf);
		ffree(info->environ);
		info->environ = NULL;
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
	else
	{
		ffree(info->argv);
		info->argv = NULL;
		info->path = NULL;
	}
}

