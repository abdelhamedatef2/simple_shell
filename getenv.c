#include "shell.h"

/**
 * get_environ - get the environment variables as an array of strings.
 * @info: pointer to a struct containing information about the environment.
 *
 * Return: an array of strings containing the environment variables.
 */
char **get_environ(info_t *info)
{
	if (info->environ == NULL || info->env_changed)
	{
		free_string_array(info->environ);
		info->environ = list_to_strings(info->env);
		info->env_changed = false;
	}

	return (info->environ);
}
/**
 * _unsetenv - remove an environment variable from the list.
 * @info: pointer to a struct containing information about the environment.
 * @var: the name of the variable to remove.
 *
 * Return: 1 if the environment was changed, or 0 otherwise.
 */
int _unsetenv(info_t *info, const char *var)
{
	list_t *current = info->env;
	list_t *previous = NULL;
	int env_changed = false;

	if (current == NULL || var == NULL)
		return (false);

	while (current != NULL)
	{
		if (_starts_with(current->str, var))
		{
			if (previous == NULL)
				info->env = current->next;
			else
				previous->next = current->next;

			free(current->str);
			free(current);
			current = previous == NULL ? info->env : previous->next;
			env_changed = true;
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}

	info->env_changed = env_changed;
	return (env_changed);
}
/**
 * _setenv - set an environment variable to a given value.
 * @info: pointer to a struct containing information about the environment.
 * @var: the name of the variable to set.
 * @value: the value to set the variable to.
 *
 * Return: true if the variable was set, or false otherwise.
 */
int _setenv(info_t *info, const char *var, const char *value)
{
	char *buf = NULL;
	list_t *node = info->env;

	if (var == NULL || value == NULL)
		return (false);

	buf = malloc(strlen(var) + strlen(value) + 2);
	if (buf == NULL)
		return (false);

	sprintf(buf, "%s=%s", var, value);

	while (node != NULL)
	{
		if (_starts_with(node->str, var))
		{
			free(node->str);
			node->str = strdup(buf);
			free(buf);
			info->env_changed = true;
			return (true);
		}
		node = node->next;
	}

	add_node_end(&(info->env), buf, 0);
	info->env_changed = true;
	return (true);
}


