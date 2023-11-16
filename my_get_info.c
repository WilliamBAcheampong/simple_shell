#include "shell.h"

/**
 * my_remove_info - Initializes info_t struct.
 *
 * @info: Address of structure.
 *
 */
void my_remove_info(info_t *info)
{
	info->path = NULL;
	info->arg = NULL;
	info->argc = 0;
	info->argv = NULL;
}

/**
 * my_info_intialise - Initializes info_t struct.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 * @arguvec: Argument vector.
 *
 */
void my_info_intialise(info_t *info, char **arguvec)
{
	int b = 0;

	info->fname = arguvec[0];
	if (info->arg)
	{
		info->argv = my_strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
			info->argv[0] = my_strdup(info->arg);
			info->argv[1] = NULL;
			}
		}
		for (b = 0; info->argv && info->argv[b]; b++)
		;
		info->argc = b;

		change_alias(info);
		my_var_change(info);
	}
}

/**
 * my_free_info  - frees info_t struct fields.
 *
  * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 * @all: If every field is freed, this is true.
 *
 */
void my_free_info(info_t *info, int all)
{
	my_jfree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buffer)
		free(info->arg);
		if (info->env)
		my_free_list(&(info->env));
		if (info->history)
		my_free_list(&(info->history));
		if (info->alias)
			my_free_list(&(info->alias));
		my_jfree(info->environ);
			info->environ = NULL;
		my_dfree((void **)info->cmd_buffer);
		if (info->readfd > 2)
		close(info->readfd);
		my_putchar(MY_BUFFER_FLUSH);
	}
}
