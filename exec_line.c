#include "main.h"

/**
 * exec_line - builtin and cmd to find
 *
 * @datash: data arg relev
 * Return: if sucess 1.
 */
int exec_line(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = get_builtin(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (cmd_exec(datash));
}
