#include "main.h"

/**
 * *nbr_spaces - return the number of occurent of a string
 * @s: string to check
 * Return: int
 */

unsigned int nbr_spaces(char *s)
{
	int i, c = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i]  == ' ')
			c++;
	}

	return (c);
}


/**
  *stringToTokens - split a sentence into multiple words.
  *@str: the string passed as argument.
  *Return: tokens
  */
char **stringToTokens(char *str)
{
int i = 0;
const char sep[] = " ";
int spaces = nbr_spaces(str);
char **toks = malloc(sizeof(char *) * (spaces + 1));
char *tok;

if (!toks)
{
	fprintf(stderr, "sh: allocation error\n");
	exit(1);
}

tok = strtok(str, sep);

while (tok != NULL)
{
	toks[i] = tok;
	tok = strtok(NULL, sep);
	i++;
}
toks[i] = NULL;

return (toks);
}
