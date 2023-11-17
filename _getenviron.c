#include "shell.h"

/**
 * get_environ - Returns the copy of the string array
 * of our environ.
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: Always returns 0.
 *
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_change)
	{
	info->environ = tostr_list(info->env);
	info->env_change = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove environment variable.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: 1 on delete, 0 otherwise.
 *
 * @var: The string env var property.
 *
 */
int _unsetenv(info_t *info, char *var)
{
	char *f;

list_t *myNode = info->env;
	size_t k = 0;

	if (!myNode || !var)
	return (0);

	while (myNode)
	{
		f = my_starts_with(myNode->str, var);
		if (f && *f == '=')
		{
		info->env_change = remove_index_node(&(info->env), k);
		k = 0;
		myNode = info->env;
		continue;
		}
		myNode = myNode->nextn;
		k++;
	}
	return (info->env_change);
}

/**
 * _setenv - Sets a new environment variable,
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
int _setenv(info_t *info, char *val, char *var)
{
	char *f;
	char *buff = NULL;
	list_t *node;

	if (!var || !val)
		return (0);

	buff = malloc(my_strlen(var) + my_strlen(val) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
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
	add_end_node(&(info->env), buff, 0);
	free(buff);
	info->env_change = 1;
	return (0);
}
