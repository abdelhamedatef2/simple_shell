#include "shell.h"
/**
 * main - Entry point for the shell program
 * @argc: Number of command line arguments
 * @argv: Array of command line argument strings
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int readfd = 2;

	/* Adjust readfd using inline assembly */
	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (readfd)
			: "r" (readfd));

	/* Open file specified in command line argument */
	if (argc == 2)
	{
		readfd = open(argv[1], O_RDONLY);
		if (readfd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = readfd;
	}

	/* Populate environment list and read history */
	populate_env_list(info);
	read_history(info);

	/* Start shell */
	hsh(info, argv);

	return (EXIT_SUCCESS);
}
