#include "shell.h"
/**
 * estwill_nodeaddition - Adds a node to the start of a list.
 * @headnode: Address to the head node pointer.
 *
 * @str: String field of node.
 * @numb: The node index used by history.
 *
 * Return: size of list is returned.
 *
 */
list_t *estwill_nodeaddition(list_t **headnode, const char *str, int numb)
{
	list_t *new_headnode;

	if (!headnode)
		return (NULL);
	new_headnode = malloc(sizeof(list_t));
	if (!new_headnode)
		return (NULL);
	estwill_setmemory((void *)new_headnode, 0, sizeof(list_t));
	new_headnode->numb = numb;
	if (str)
	{
		new_headnode->str = estwill_strdup(str);
		if (!new_headnode->str)
		{
		free(new_headnode);
			return (NULL);
		}
	}
	new_headnode->nextn = *headnode;
	*headnode = new_headnode;
	return (new_headnode);
}

/**
 * estwill_add_node_at_end - Adds a node to the end of a list.
 * @head_node: address to head_node pointer.
 *
 * @str: Node’s string field.
 * @numb: The node index used by history.
 *
 * Return:  returns size of list.
 */
list_t *estwill_add_node_at_end(list_t **head_node, const char *str, int numb)
{
	list_t *new_node, *node;

	if (!head_node)
		return (NULL);

	node = *head_node;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	estwill_setmemory((void *)new_node, 0, sizeof(list_t));
	new_node->numb = numb;
	if (str)
	{
		new_node->str = estwill_strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->nextn)
			node = node->nextn;
		node->nextn = new_node;
	}
	else
		*head_node = new_node;
	return (new_node);
}

/**
 * estwill_string_list_print - prints only the strings
 * of the list_t linked list.
 *
 * @n: Pointer to the beginning node.
 *
 * Return: returns size of list.
 *
 */
size_t estwill_string_list_print(const list_t *n)
{
	size_t v = 0;

	while (n)
	{
		_willputs(n->str ? n->str : "(nill)");
		_willputs("\n");
		n = n->nextn;
		v++;
	}
	return (v);
}

/**
 * estwill_remove_index_node  - Deletes node at a specified index.
 * @head_node: Address of first node pointer.
 * @indnode: Indnode of node to be deleted.
 *
 * Return: 0 if it fails, 1 on success.
 *
 */
int estwill_remove_index_node(list_t **head_node, unsigned int indnode)
{
	unsigned int r = 0;

list_t *node, *previousnode;

	if (!head_node || !*head_node)
		return (0);

	if (!indnode)
	{
		node = *head_node;
		*head_node = (*head_node)->nextn;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head_node;
	while (node)
	{
		if (r == indnode)
		{
		previousnode->nextn = node->nextn;
		free(node->str);
		free(node);
		return (1);
		}
	r++;
	previousnode = node;
	node = node->nextn;
	}
	return (0);
}

/**
 * estwill_free_list - Frees every node of the list.
 * @head_node_ptr: Address of head_node pointer.
 *
 * Return: returns void.
 */
void estwill_free_list(list_t **head_node_ptr)
{
	list_t *node, *head_node, *nextn_node;

	if (!head_node_ptr || !*head_node_ptr)
		return;
	head_node = *head_node_ptr;
	node = head_node;
	while (node)
	{
	nextn_node = node->nextn;
	free(node->str);
	free(node);
	node = nextn_node;
	}
	*head_node_ptr = NULL;
}
