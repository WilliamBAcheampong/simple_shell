#include "shell.h"
/**
 * my_nodeAdd - Adds a node to the start of a list.
 * @headNode: Address to the head node pointer.
 *
 * @str: String field of node.
 * @numb: The node index used by history.
 *
 * Return: size of list is returned.
 *
 */
list_t *my_nodeAdd(list_t **headNode, const char *str, int numb)
{
	list_t *new_headNode;

	if (!headNode)
		return (NULL);
	new_headNode = malloc(sizeof(list_t));
	if (!new_headNode)
		return (NULL);
	my_setmemory((void *)new_headNode, 0, sizeof(list_t));
	new_headNode->numb = numb;
	if (str)
	{
		new_headNode->str = _strdup(str);
		if (!new_headNode->str)
		{
		free(new_headNode);
			return (NULL);
		}
	}
	new_headNode->nextn = *headNode;
	*headNode = new_headNode;
	return (new_headNode);
}

/**
 * add_end_node - Adds a node to the end of a list.
 * @head_node: address to head_node pointer.
 *
 * @str: Node’s string field.
 * @numb: The node index used by history.
 *
 * Return:  returns size of list.
 */
list_t *add_end_node(list_t **head_node, const char *str, int numb)
{
	list_t *new_node, *node;

	if (!head_node)
		return (NULL);

	node = *head_node;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	my_setmemory((void *)new_node, 0, sizeof(list_t));
	new_node->numb = numb;
	if (str)
	{
		new_node->str = _strdup(str);
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
 * my_string_list_print - prints only the strings
 * of the list_t linked list.
 *
 * @n: Pointer to the beginning node.
 *
 * Return: returns size of list.
 *
 */
size_t my_string_list_print(const list_t *n)
{
	size_t v = 0;

	while (n)
	{
		_puts(n->str ? n->str : " (nill) ");
		_puts("\n");
		n = n->nextn;
		v++;
	}
	return (v);
}

/**
 * remove_index_node  - Deletes node at a specified index.
 * @head_node: Address of first node pointer.
 * @indnode: Indnode of node to be deleted.
 *
 * Return: 0 if it fails, 1 on success.
 *
 */
int remove_index_node(list_t **head_node, unsigned int indnode)
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
 * my_free_list - Frees every node of the list.
 * @head_node_ptr: Address of head_node pointer.
 *
 * Return: returns void.
 */
void my_free_list(list_t **head_node_ptr)
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
