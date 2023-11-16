#include "shell.h"
/**
 * my_history - history list is displayed, line
 * by line, beginning with line numbers, commencing from 0.
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 *  Return: always 0.
 *
 */
int my_history(info_t *info)
{
	list_print(info->history);
	return (0);
}

/**
 * unset_alias - string is set unto by alias.
 *
 * @info:   Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * @str: Alias of string.
 *
 * Return: 0 on success, failure is 1.
 *
 */
int unset_alias(info_t *info, char *str)
{
	int ret;
char *f, y;


	f = my_strchr(str, '=');
	if (!f)
		return (1);
	y = *f;
	*f = 0;
	ret = remove_index_node(&(info->alias),
	get_indexOf_node(info->alias, node_start(info->alias, str, -1)));
	*f = y;
	return (ret);
}

/**
 * set_alias - Sets alias to string.
 * @info: Parameter struct.
 *
 * @str: The string alias.
 *
 * Return: 1 if failure , upon success, return 0.
 *
 */
int set_alias(info_t *info, char *str)
{
char *f;

	f = my_strchr(str, '=');
	if (!f)
		return (1);
	if (!*++f)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_end_node(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias of a string.
 *
 * @node: alias node.
 *
 * Return: if 0, success, 1 if failure.
 *
 */
int print_alias(list_t *node)
{
	char *f = NULL, *k = NULL;

	if (node)
	{
		f = my_strchr(node->str, '=');
		for (k = node->str; k <= f; k++)
		my_putchar(*k);
		my_putchar('\'');
		_willputs(f + 1);
		_willputs("'\n");
		return (0);
	}
	return (1);
}

/**
 * _ouralias - Mimics the alias builtin (man alias).
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 *  Return: 0.
 *
 */
int _ouralias(info_t *info)
{
	list_t *myNode = NULL;

int r = 0;
	char *f = NULL;

	if (info->argc == 1)
	{
		myNode = info->alias;
		while (myNode)
		{
		print_alias(myNode);
		myNode = myNode->nextn;
		}
		return (0);
	}

	for (r = 1; info->argv[r]; r++)
	{
		f = my_strchr(info->argv[r], '=');
		if (f)
		set_alias(info, info->argv[r]);
		else
		print_alias(node_start(info->alias, info->argv[r], '='));
	}

	return (0);
}
