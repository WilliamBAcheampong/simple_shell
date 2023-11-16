#include "shell.h"

/**
 * len_ofList - Find out len of linked list.
 * @n: First node pointer.
 *
 * Return: list size.
 *
 */
size_t len_ofList(const list_t *n)
{
	size_t g = 0;

	while (n)
	{
		n = n->nextn;
		g++;
	}
	return (g);
}

/**
 * tostr_list - An array of strings of the list->str is returned.
 * @headNode: first node pointer.
 *
 * Return: Array of strings.
 *
 */
char **tostr_list(list_t *headNode)
{
	char *str;
	size_t d = len_ofList(headNode), f;
	char **strings;
	list_t *node1 = headNode;


	if (!headNode || !d)
		return (NULL);
	strings = malloc(sizeof(char *) * (d + 1));
	if (!strings)
		return (NULL);
	for (d = 0; node1; node1 = node1->nextn, d++)
	{
		str = malloc(my_strlen(node1->str) + 1);
		if (!str)
		{
			for (f = 0; f < d; f++)
			free(strings[f]);
			free(strings);
			return (NULL);
		}

	str = _strcpy(str, node1->str);
	strings[d] = str;
	}
	strings[d] = NULL;
	return (strings);
}

/**
 * list_print - Prints all elements of the list_t linked list.
 *
 * @n: Points to the first node.
 *
 * Return: returns size of the list.
 *
 */
size_t list_print(const list_t *n)
{
	size_t e = 0;

	while (n)
	{
		_willputs(my_change_num(n->numb, 10, 0));
		my_putchar(':');
		my_putchar(' ');
		_willputs(n->str ? n->str : "(nil)");
		_willputs("\n");
		n = n->nextn;
		e++;
	}
	return (e);
}

/**
 * node_start - Returns node with
 * prefix starting string.
 *
 * @hnode: list head pointer.
 *
 * @prefstr: String to match what we want.
 * @c: after prefix to match, this is the next char.
 *
 * Return: Returns null or match node
 *
 */
list_t *node_start(list_t *hnode, char *prefstr, char c)
{
	char *f = NULL;

	while (hnode)
	{
		f = my_starts_with(hnode->str, prefstr);
		if (f && ((c == -1) || (*f == c)))
			return (hnode);
		hnode = hnode->nextn;
	}
	return (NULL);
}

/**
 * get_indexOf_node - Gets the index of a node.
 * @headNode: list head pointer.
 *
 * @my_node: node pointer.
 *
 * Return: returns index of node or return -1.
 *
 */
ssize_t get_indexOf_node(list_t *headNode, list_t *my_node)
{
	size_t q = 0;

	while (headNode)
	{
		if (headNode == my_node)
			return (q);
		headNode = headNode->nextn;
		q++;
	}
	return (-1);
}
