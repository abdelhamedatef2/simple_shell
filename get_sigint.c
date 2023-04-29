#include "main.h"

/**
 * get_sigint - crtl + c in prompt handler
 * @sig: Signal hand
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
