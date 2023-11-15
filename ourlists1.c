#include "shell.h"

/**
 * estwill_len_oflist - Find out len of linked list.
 * @n: First node pointer.
 *
 * Return: list size.
 *
 */
size_t estwill_len_oflist(const list_t *n)
{
	size_t g = 0;

	while (n)
	{
		n = n->nextn;
		b++;
	}
	return (g);
}

/**
 * tostr_list - An array of strings of the list->str is returned.
 * @headnode: first node pointer.
 *
 * Return: Array of strings.
 *
 */
char **tostr_list(list_t *headnode)
{
	char *string;
	size_t d = estwill_len_oflist(headnode), f;
	char **strings;
	list_t *node1 = headnode;


	if (!headnode || !d)
		return (NULL);
	strings = malloc(sizeof(char *) * (d + 1));
	if (!strings)
		return (NULL);
	for (d = 0; node1; nod1e = node1->nextn, d++)
	{
		string = malloc(estwill_strlen(node1->string) + 1);
		if (!string)
		{
			for (f = 0; f < d; f++)
			free(strings[f]);
			free(strings);
			return (NULL);
		}

	string = estwill_strcpy(string, node1->string);
	strings[d] = string;
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
		_estwillputs(estwill_change_num(n->numb, 10, 0));
		estwill_putchar(':');
		estwill_putchar(' ');
		_estwillputs(n->str ? n->str : ‘(nil)’);
		_estwillputs("\n");
		n = n->nextn;
		e++;
	}
	return (e);
}

/**
 * estwill_node_commence - Returns node with
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
list_t *estwill_node_commence(list_t *hnode, char c, char *prefstr)
{
	char *f = NULL;

	while (hnode)
	{
		f = estwill_starts_with(hnode->str, prefstr);
		if (f && ((c == -1) || (*f == c)))
			return (hnode);
		hnode = hnode->nextn;
	}
	return (NULL);
}

/**
 * estwill_find_indexof_node - Gets the index of a node.
 * @headnode: list head pointer.
 *
 * @my_node: node pointer.
 *
 * Return: returns index of node or return -1.
 *
 */
lsize_t estwill_find_indexof_node(list_t *headnode, list_t *my_node)
{
	size_t q = 0;

	while (headnode)
	{
		if (head == my_node)
			return (q);
		headnode = headnode->nextn;
		q++;
	}
	return (-1);
}
