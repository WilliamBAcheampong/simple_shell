#include "shell.h"

/**
 * ischain - Test if current char in buffer is a chain delimiter.
 * @info: the parameter struct.
 *
 * @buff1: the buffer for char .
 *
 *
 * @k: address of current position in buffer.
 *
 *
 * Return: 1 if chain delimiter, 0 if nor chain delimeter
 */
int ischain(info_t *info, char *buff1, size_t *k)
{
	size_t g = *k;


	if (buff1[g] == '|' && buff1[g + 1] == '|')
	{
	buff1[g] = 0;
	g++;
	info->cmd_buffer_type = MY_COMMAND_OR;
	}
	else if (buff1[g] == '&' && buff1[g + 1] == '&')
	{
		buff1[g] = 0;
		g++;
		info->cmd_buffer_type = MY_COMMAND_AND;
	}
	else if (buff1[g] == ';') /* End of command*/
	{
	buff1[g] = 0; /* Null replaces semi-colon*/
	info->cmd_buffer_type = MY_COMMAND_CHAIN;
	}
	else
	return (0);

*k = g;
	return (1);
}

/**
 * my_check_chain - Check to know if to continue chaining
 *  based on last status.
* @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * @buff1: the char buffer.
 *
 * @b: address of current position in buff1.
 * @f: beginning position in buff1.
 *
 * @len: len of buff1.
 *
 * Return: Void.
 *
 */
void my_check_chain(info_t *info, char *buff1, size_t *b, size_t f, size_t len)
{
	size_t k = *b;

	if (info->cmd_buffer_type == MY_COMMAND_AND)
	{
		if (info->status)
		{
			buff1[f] = 0;
			k = len;
		}
	}
	if (info->cmd_buffer_type == MY_COMMAND_OR)
	{
		if (!info->status)
		{
			buff1[f] = 0;
			k = len;
		}
	}

	*b = k;
}

/**
 * change_alias - Replaces an aliases in the tokenized string.
* @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: 1 if replaced, 0 if not replaced.
 *
 */
int change_alias(info_t *info)
{
	char *f;
int k;
	list_t *node;

	for (k = 0; k < 10; k++)
	{
		node = node_start(info->alias, info->argv[0], '=');
		if (!node)
		return (0);

free(info->argv[0]);
		f = my_strchr(node->str, '=');
		if (!f)
		return (0);

f = my_strdup(f + 1);
		if (!f)
			return (0);
		info->argv[0] = f;
	}
	return (1);
}

/**
 * my_var_change - Replaces vars in tokenized string.
 *
* @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: 1 if replaced, 0 if opposite
 *
 */
int my_var_change(info_t *info)
{
	int e = 0;

	list_t *node;

	for (e = 0; info->argv[e]; e++)
	{
		if (info->argv[e][0] != '$' || !info->argv[e][1])
			continue;

		if (!_strcmp(info->argv[e], "$?"))
		{
			my_str_change(&(info->argv[e]),
			my_strdup(my_change_num(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[e], "$$"))
		{
			my_str_change(&(info->argv[e]),
			my_strdup(my_change_num(getpid(), 10, 0)));
			continue;
		}
		node = node_start(info->env, &info->argv[e][1], '=');
		if (node)
		{
			my_str_change(&(info->argv[e]),
				my_strdup(my_strchr(node->str, '=') + 1));
			continue;
		}
		my_str_change(&info->argv[e], my_strdup(""));

	}
	return (0);
}

/**
 * my_str_change - Replaces string.
 *
 * @old_address: old string address.
 *
 * @new_address: new string address.
 *
 * Return: 1 if replaced, 0 if not.
 *
 */
int my_str_change(char **old_address, char *new_address)
{
	free(*old_address);
	*old_address = new_address;
	return (1);
}
