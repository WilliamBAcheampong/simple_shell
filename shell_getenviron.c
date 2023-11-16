#include "shell.h"

/**
 * my_get_environ - Returns the copy of the string array
 * of our environ.
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: Always returns 0.
 *
 */
char **my_get_environ(info_t *info)
{
	if (!info->environ || info->env_change)
	{
	info->environ = tostr_list(info->env);
	info->env_change = 0;
	}

	return (info->environ);
}

/**
 * my_unsetenv - Remove environment variable.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: 1 on delete, 0 otherwise.
 *
 * @var: The string env var property.
 *
 */
int my_unsetenv(info_t *info, char *var)
{
	char *f;

list_t *mynode = info->env;
	size_t k = 0;

	if (!mynode || !var)
	return (0);

	while (mynode)
	{
		f = my_starts_with(mynode->str, var);
		if (f && *f == '=')
		{
		info->env_change = my_remove_index_node(&(info->env), k);
		k = 0;
		mynode = info->env;
		continue;
		}
		mynode = mynode->nextn;
		k++;
	}
	return (info->env_change);
}

/**
 * my_setenv - Sets a new environment variable,
 * or modify an existing one.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * @var: Property of string env var.
 *
 * @val: String env var’s value.
 *  Return:  0.
 *
 */
int my_setenv(info_t *info, char *val, char *var)
{
	char *f;
	char *buff = NULL;
	list_t *node;

	if (!var || !val)
		return (0);

	buff = malloc(my_strlen(var) + my_strlen(val) + 2);
	if (!buff)
		return (1);
	my_strcpy(buff, var);
	my_strcat(buff, "=");
	my_strcat(buff, val);
	node = info->env;
	while (node)
	{
		f = my_starts_with(node->str, var);
		if (f && *f == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_change = 1;
			return (0);
		}
		node = node->nextn;
	}
	my_add_node_at_end(&(info->env), buff, 0);
	free(buff);
	info->env_change = 1;
	return (0);
}
