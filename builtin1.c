#include "shell.h"
/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Pointer to the info_t struct
 *
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	history_t *node;
	int count = 0;

	/* Traverse the history list and print each command */
	for (node = info->history; node != NULL; node = node->next)
	{
		_puts(_itoa(count));
		_puts("  ");
		_puts(node->command);
		_putchar('\n');
		count++;
	}

	return (0);
}
/**
 * unset_alias - removes an alias from the alias list
 * @info: Pointer to the info_t struct
 * @str: the string alias
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}
/**
 * set_alias - adds an alias to the alias list
 * @info: Pointer to the info_t struct
 * @alias_str: The alias string to add
 *
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *alias_str)
{
	/* Check if the alias contains an equal sign */
	char *equal_sign = _strchr(alias_str, '=');

	if (!equal_sign)
		return (1);

	/* Replace the equal sign with a null terminator */
	*equal_sign = '\0';

	/* Get the alias name and value */
	char *alias_name = alias_str;
	char *alias_value = equal_sign + 1;

	/* Create a new alias node */
	alias_t *new_node = create_alias_node(alias_name, alias_value);

	if (!new_node)
	{
		/* Restore the equal sign and return an error */
		*equal_sign = '=';
		return (1);
	}

	/* Add the node to the alias list */
	add_node(&(info->alias), new_node);

	/* Restore the equal sign and return success */
	*equal_sign = '=';
	return (0);
}
/**
 * print_alias - prints an alias string
 * @node: Pointer to the alias node to print
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	if (!node)
		return (91);

	char *alias = node->str;
	char *equal_sign = _strchr(alias, '=');

	if (!equal_sign)
		return (1);

	/* Print the alias name and value */
	*equal_sign = '\0';
	_puts(alias);
	_putchar('\'');
	_puts(equal_sign + 1);
	_puts("'\n");
	*equal_sign = '=';

	return (0);
}
/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Pointer to the info_t struct
 *
 * Return: Always 0
 */

int _myalias(info_t *info)
{
	/* Check if no arguments were provided */
	if (info->argc == 1)
	{
		/* Print all aliases */
		print_all_aliases(info->alias);
		return (0);
	}

	/* Loop through each argument */
	for (int i = 1; i < info->argc; i++)
	{
		/* Check if the argument contains an equal sign */
		char *equal_sign = _strchr(info->argv[i], '=');

		if (equal_sign)
		{
			/* Set an alias */
			set_alias(info, info->argv[i]);
		}
		else
		{
			/* Print a specific alias */
			print_alias_node(find_node(info->alias, info->argv[i]));
		}
	}

	return (0);
}
