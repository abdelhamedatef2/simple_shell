#include "shell.h"

/**
 * is_cmd - Checks if a path corresponds to a regular file
 * @info: Pointer to the shell info struct (unused)
 * @path: Path to check
 *
 * Return: 1 if path corresponds to a regular file, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;

	if (!path || stat(path, &st))
	{
		return (0);
	}

	if (S_ISREG(st.st_mode))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/**
 * dup_chars - Duplicates a substring of characters from a string
 * @pathstr: String to copy from
 * @start: Index of the first character to copy
 * @stop: Index of the stop character (exclusive)
 *
 * Return: Pointer to the duplicated substring
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int i, x = 0;

	for (i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
		{
			buffer[x++] = pathstr[i];
		}
	}
	buffer[x] = '\0';
	return (buffer);
}
/**
 * find_path - searches for a command in the directories specified by PATH
 * @info: a pointer to a struct containing information about the environment
 * @pathstr: a colon-separated list of directories to search
 * @cmd: the command to search for
 *
 * Return: a pointer to a string containing the full path to the command if found,
 *         or NULL if the command was not found or if pathstr is NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	if (!pathstr)
		return (NULL);

	if (starts_with(cmd, "./") && is_cmd(info, cmd))
		return (cmd);

	char *path = NULL;

	while (*pathstr)
	{
		char *end = pathstr;
		while (*end && *end != ':')
			end++;

		int path_len = end - pathstr;
		path = malloc(path_len + strlen(cmd) + 2);
		if (!path)
			return (NULL);

		strncpy(path, pathstr, path_len);
		path[path_len] = '/';
		strcpy(&path[path_len+1], cmd);

		if (is_cmd(info, path))
			return (path);

		if (*end)
			pathstr = end + 1;
		else
			pathstr = end;
	}

	free(path);
	return (NULL);
}
