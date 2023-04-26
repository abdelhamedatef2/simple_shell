#include "shell.h"

/**
 * hsh - main shell function
 * @info: pointer to info_t struct
 * @av: array of arguments
 *
 * Return: the return value of the last built-in command executed
 */
int hsh(info_t *info, char **av)
{
	int builtin_return = 0;

	do {
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);

		ssize_t r = get_input(info);

		if (r == -1)
			break;

		set_info(info, av);
		builtin_return = find_builtin(info);
		if (builtin_return == -1)
			find_cmd(info);

		free_info(info, 0);
	} while (builtin_return != -2);

	write_history(info);
	free_info(info, 1);

	if (!interactive(info) && info->status)
		exit(info->status);

	if (builtin_return == -2)
		exit(info->err_num == -1 ? info->status : info->err_num);

	return (builtin_return);
}
/**
 * find_builtin - find and execute a built-in command
 * @info: pointer to info_t struct
 *
 * Return: the return value of the built-in command, or -1 if not found
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}
/**
 * find_cmd - find and execute a command
 * @info: pointer to info_t struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int num_args = 0;

	info->path = info->argv[0];
	if (info->linecount_flag)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (char **arg = info->arg; *arg; arg++)
	{
		if (!is_delim(*arg, " \t\n"))
			num_args++;
	}

	if (!num_args)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	} else
	{
		if ((interactive(info) || _getenv(info, "PATH=") ||
		     info->argv[0][0] == '/') && is_cmd(info, info->argv[0])) {
			fork_cmd(info);
		} else if (*info->arg != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}
/**
 * fork_cmd - Forks a child process to execute a command.
 * @info: A pointer to an info_t struct containing
 * information about the command.
 */
void fork_cmd(info_t *info)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&info->status);
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
