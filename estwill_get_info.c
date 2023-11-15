#include "shell.h"

/**
 * estwill_remove_info - Initializes info_t struct.
 *
 * @info: Address of structure.
 *
 */
void estwill_remove_info(info_t *info)
{
	info->path = NULL;
	info->arg = NULL;
	info->argc = 0;
	info->argv = NULL;
}

/**
 * estwill_info_intialise - Initializes info_t struct.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 * @arguvec: Argument vector.
 *
 */
void estwill_info_intialise(info_t *info, char **arguvec)
{
	int b = 0;

	info->fname = arguvec[0];
	if (info->arg)
	{
		info->argv = estwill_strtok(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
			info->argv[0] = estwill_strdup(info->arg);
			info->argv[1] = NULL;
			}
		}
		for (b = 0; info->argv && info->argv[b]; b++)
		;
		info->argc = b;

		estwill_alias_change(info);
		estwill_var_change(info);
	}
}

/**
 * estwill_free_info  - frees info_t struct fields.
 *
  * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 * @all: If every field is freed, this is true.
 *
 */
void estwill_free_info(info_t *info, int all)
{
	estwill_jfree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buffer)
		free(info->arg);
		if (info->env)
		estwill_free_list(&(info->env));
		if (info->history)
		estwill_free_list(&(info->history));
		if (info->alias)
			estwill_free_list(&(info->alias));
		estwill_jfree(info->environ);
			info->environ = NULL;
		estwill_dfree((void **)info->cmd_buffer);
		if (info->readfd > 2)
		close(info->readfd);
		estwill_putchar(ESTWILL_BUFFER_FLUSH);
	}
}
