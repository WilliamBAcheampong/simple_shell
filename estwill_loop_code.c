#include "shell.h"
/**
 * hshell - Main loop of shell.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 * @arguvec: The argument vector from main function.
 *
 * Return: Error code or 0 when success, 1 when error.
 *
 */
int hshell(info_t *info, char **arguvec)
{
	int builtin_ret = 0;
	ssize_t f = 0;

	while (f != -1 && builtin_ret != -2)
	{
		estwill_remove_info(info);
		if (estwill_interactive(info))
		_estwillputs("$ ");
		_estwillputchar(ESTWILL_BUFFER_FLUSH);
		f = estwill_get_input(info);
		if (f != -1)
		{
			estwill_info_intialise(info, arguvec);
			builtin_ret = look_for_builtin(info);
		if (builtin_ret == -1)
			getcmd(info);
		}
		else if (estwill_interactive(info))
		estwill_putchar('\n');
		estwill_free_info(info, 0);
	}
	estwill_hist_record(info);
	estwill_free_info(info, 1);
	if (!estwill_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->errcode_numb == -1)
			exit(info->status);
		exit(info->errcode_numb);
	}
	return (builtin_ret);
}

/**
 * look_for_builtin - Finds appropriate command that is builtin
 *
* @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit().
 *
 */
int look_for_builtin(info_t *info)
{
	int e, built_in_ret = -1;
	builtin_table builtintable[] = {
	{"exit", estwill_exit},
	{"env", _ourenv},
	{"help", estwill_help},
	{"history", estwill_ourhist},
	{"setenv", _oursetenv},
	{"unsetenv", _myunsetenv},
	{"cd", estwill_mcd},
	{"alias", estwill_ouralias},
	{NULL, NULL}
	};

	for (e = 0; builtintable[e].type; e++)
		if (estwill_strcmp(info->argv[0], builtintable[e].type) == 0)
		{
			info->errline_cnt++;
			built_in_ret = builtintable[e].funct(info);
			break;
		}
	return (built_in_ret);
}

/**
 * getcmd - Finds a command in PATH.
 * @info: The parameter & return info struct.
 * 
 *
 * Return: returns void.
 *
 */
void getcmd(info_t *info)
{
	char *path = NULL;
	int u, k;

	info->path = info->argv[0];
	if (info->linecnt_flag == 1)
	{
		info->errline_cnt++;
		info->linecnt_flag = 0;
	}
	for (u = 0, k = 0; info->arg[u]; u++)
		if (!is_delimi(info->arg[u], " \t\n"))
		k++;
	if (!k)
	return;

	path = estwill_get_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
	info->path = path;
	forkew_cmd(info);
	}
	else
	{
		if ((estwill_interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && estwill_is_cmd(info, info->argv[0]))
			forkew_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			estwill_errorPrint(info, "It cannot be found\n");
		}
	}
}

/**
 * forkew_cmd - Forks an executing thread to run command.
* @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: void.
 *
 */
void forkew_cmd(info_t *info)
{
	pid_t child_pid1;

	child_pid1 = fork();
	if (child_pid1 == -1)
	{
		/* TODO: PUT ERROR FUNCTION, error */
		perror("Error!:");
		return;
	}
	if (child_pid1 == 0)
	{
		if (execve(info->path, info->argv, estwill_get_environ(info)) == -1)
		{
			estwill_free_info(info, 1);
			if (errno == EACCES)
			exit(126);
			exit(1);
		}
		/* TODO: PUT FUNCTION, error*/
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				estwill_errorPrint(info, "Permission is not allowed\n");
		}
	}
}
