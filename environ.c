#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}
/**
 * _getenv - gets the value of an environment variable
 * @info: pointer to structure containing potential arguments
 * @name: name of the environment variable
 *
 * Return: pointer to the value of the
 * environment variable, or NULL if not found
 */
char *_getenv(info_t *info, const char *name)
{
	const list_t *node = info->env;

	while (node != NULL)
	{
		const char *var = node->str;
		const char *value = strchr(var, '=');
		size_t var_len = value - var;

		if (var_len == strlen(name) && strncmp(var, name, var_len) == 0)
		{
			return ((char *) (value + 1));
		}
		node = node->next;
	}
	return (NULL);
}
/**
 * _mysetenv - Initializes a new environment
 * variable or modifies an existing one
 * @info: pointer to structure containing potential arguments
 *
 * Return: 0 on success, 1 on failure
 */
int _mysetenv(info_t *info)
{
	const int expected_argc = 3;
	int ret_val = 1;

	if (info->argc == expected_argc)
	{
		if (_setenv(info, info->argv[1], info->argv[2]) == 0)
		{
			ret_val = 0;
		}
	}
	else
	{
		fprintf(stderr, "Error: incorrect number of arguments\n");
	}

	return (ret_val);
}
/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}
/**
 * populate_env_list - create a linked list of environment variables
 * @info: pointer to a structure containing potential arguments
 * Return: 0 on success
 */
int populate_env_list(info_t *info)
{
	/* Create a new linked list to hold environment variables */
	list_t *head = NULL;
	list_t *tail = NULL;

	/* Iterate through the array of environment variables */
	for (char **env = environ; *env; env++)
	{
		/* Add a new node to the linked list for this environment variable */
		list_t *node = malloc(sizeof(list_t));

		if (!node)
			return (-1); /* error: out of memory */
		node->str = strdup(*env);

		if (!node->str)
		{
			free(node);
			return (-1); /* error: out of memory */
		}
		node->next = NULL;

		/* Add the new node to the end of the linked list */
		if (!head)
			head = node;
		if (tail)
			tail->next = node;
		tail = node;
	}

	/* Set the info->env pointer to the head of the linked list */
	info->env = head;

	return (0); /* success */
}
