#include "shell.h"

/**
 * _myexit - Exits the shell with the given status code
 * @info: Pointer to info_t struct
 *
 * Return: -2 to signal exit
 */
int _myexit(info_t *info)
{
	if (info->argv[1])
	{
		char *arg = info->argv[1];
		int exitcode = 0;

		/* Convert the argument to an integer */
		for (; *arg; arg++)
		{
			if (*arg < '0' || *arg > '9')
			{
				info->status = 2;
				print_error(info, "Illegal number: ");
				_eputs(info->argv[1]);
				_eputchar('\n');
				return (1);
			}
			exitcode = exitcode * 10 + (*arg - '0');
		}

		info->err_num = exitcode;
	}

	return (-2);
}
/**
 * _mycd - changes the current directory of the process
 * @info: Pointer to the info_t struct
 *
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char buffer[1024];
	char *dir = info->argv[1] ? info->argv[1] : _getenv(info, "HOME=");

	if (!dir)
		dir = _getenv(info, "PWD=");
	if (_strcmp(dir, "-") == 0)
		dir = _getenv(info, "OLDPWD=");
	if (!dir)
	{
		char *cwd = getcwd(buffer, 1024);

		_puts(cwd ? cwd : "TODO: >>getcwd failure emsg here<<\n");
		return (1);
	}

	int chdir_ret = chdir(dir);

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(dir), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", getcwd(buffer, 1024));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}

	return (0);
}
/**
 * _myhelp - prints help information for the shell
 * @info: Pointer to the info_t struct
 *
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	/* A list of shell commands and their descriptions */
	char *help_text[] = {
		"help - Display this help message",
		"cd - Change the current working directory",
		"env - Display the environment variables",
		"exit - Exit the shell",
		NULL /* End of list marker */
	};
	char **command = help_text;

	/* Print the help information for each command */
	while (*command)
	{
		_puts(*command);
		_putchar('\n');
		command++;
	}

	/* Ignore unused variable warning */
	(void)info->argv;

	return (0);
}
