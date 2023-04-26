#include "shell.h"
/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file or NULL on failure
 */
char *get_history_file(info_t *info)
{
	char *filename_buf, *home_dir;

	home_dir = _getenv(info, "HOME=");
	if (!home_dir)
		return (NULL);
	filename_buf = malloc(sizeof(char) * (_strlen(home_dir)
				+ _strlen(HIST_FILE) + 2));
	if (!filename_buf)
		return (NULL);
	filename_buf[0] = '\0';
	_strcpy(filename_buf, home_dir);
	_strcat(filename_buf, "/");
	_strcat(filename_buf, HIST_FILE);
	return (filename_buf);
}
/**
 * write_history - writes the history list to a file
 * @info: parameter struct
 *
 * Return: 1 on success, -1 on failure
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename;
	list_t *node;

	filename = get_history_file(info);
	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
	{
		free(filename);
		return (-1);
	}

	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);

	close(fd);
	free(filename);
	return (1);
}
/**
 * read_history - reads the history file into a linked list
 * @info: parameter struct
 *
 * Return: number of history entries added to the list, or 0 on failure
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}
/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}
/**
 * renumber_history - renumbers the history list nodes
 * @info: parameter struct
 *
 * Return: number of nodes in the history list
 */
int renumber_history(info_t *info)
{
	list_t *current_node = info->history;
	int node_count = 0;

	while (current_node)
	{
		current_node->num = node_count++;
		current_node = current_node->next;
	}

	info->histcount = node_count;
	return (node_count);
}
