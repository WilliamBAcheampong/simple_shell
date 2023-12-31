#include "shell.h"

/**
 * _myenv - Print the current env
 *
  * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: Return 0.
 *
 */
int _myenv(info_t *info)
{
	my_string_list_print(info->env);
	return (0);
}

/**
 * _getenv - Gets the value of an environ variable.
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * @name: name of env var
 *
 * Return: The value.
 *
 */
char *_getenv(info_t *info, const char *name)
{
char *f;
list_t *node = info->env;

	while (node)
	{
		f = my_starts_with(node->str, name);
		if (f && *f)
			return (f);
		node = node->nextn;
	}
	return (NULL);
}

/**
 * __mysetenv - Sets a new environment variable or make
 * changes an existing one.
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 * Return: 0.
 *
 */
int __mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_myputs("Number of arguments is wrong\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Clear or remove an environment variable.
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: 0.
 *
 */
int _myunsetenv(info_t *info)
{
	int d;

	if (info->argc == 1)
	{
	_myputs("Arguments are not enough.\n");
	return (1);
	}
	for (d = 1; d <= info->argc; d++)
		_unsetenv(info, info->argv[d]);

	return (0);
}

/**
 * populate_env_list - Fills env linked list.
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: always returns 0.
 *
 */
int populate_env_list(info_t *info)
{

size_t d;
list_t *node1 = NULL;

	for (d = 0; environ[d]; d++)
	add_end_node(&node1, environ[d], 0);
	info->env = node1;
	return (0);
}
