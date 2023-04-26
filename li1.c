#include "shell.h"
/**
 * list_len - calculates the length of a linked list
 * @head: pointer to the head node
 *
 * Return: number of nodes in the list
 */
size_t list_len(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}

	return (count);
}
/**
 * list_to_strings - converts a linked list of strings to an array of strings
 * @head: pointer to the head node
 *
 * Return: pointer to the array of strings, or NULL on failure
 */
char **list_to_strings(list_t *head)
{
	size_t count, i, j;
	char **strs, *str;
	list_t *node;

	count = list_len(head);
	if (!head || !count)
		return (NULL);

	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);

	node = head;
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}

	strs[i] = NULL;
	return (strs);
}
/**
 * print_list - prints a linked list of numbers and strings
 * @h: pointer to the head node
 *
 * Return: number of nodes in the list
 */
size_t print_list(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}

	return (count);
}
/**
 * node_starts_with - finds the first node with a string starting with a prefix
 * @node: pointer to the first node
 * @prefix: prefix to search for
 * @c: optional character to match after the prefix
 *
 * Return: pointer to the first matching node, or NULL if not found
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && (c == -1 || *p == c))
			return (node);
		node = node->next;
	}

	return (NULL);
}
/**
 * get_node_index - returns the index of a node in a linked list
 * @head: pointer to the head node
 * @node: pointer to the node to find
 *
 * Return: index of the node, or -1 if not found
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}

	return (-1);
}

