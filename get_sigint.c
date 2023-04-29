#include "main.h"

/**
 * get_sigint - Handle the crtl + c when occure in prmp
 * @sig: handler sig
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
