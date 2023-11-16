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
		my_remove_info(info);
		if (my_interactive(info))
		_willputs("$ ");
		_myputchar(MY_BUFFER_FLUSH);
		f = my_get_input(info);
		if (f != -1)
		{
			my_info_intialise(info, arguvec);
			builtin_ret = look_for_builtin(info);
		if (builtin_ret == -1)
			getcmd(info);
		}
		else if (my_interactive(info))
		my_putchar('\n');
		my_free_info(info, 0);
	}
	_history_write(info);
	my_free_info(info, 1);
	if (!my_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_number == -1)
			exit(info->status);
		exit(info->err_number);
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
	{"exit", my_exit},
	{"env", _ourenv},
	{"help", my_help},
	{"history", my_history},
	{"setenv", _oursetenv},
	{"unsetenv", _myunsetenv},
	{"cd", my_mcd},
	{"alias", _ouralias},
	{NULL, NULL}
	};

	for (e = 0; builtintable[e].type; e++)
		if (_strcmp(info->argv[0], builtintable[e].type) == 0)
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
		if (!is_delimiter(info->arg[u], " \t\n"))
		k++;
	if (!k)
	return;

	path = _get_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
	info->path = path;
	fork_cmd(info);
	}
	else
	{
		if ((my_interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && my_is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			error_print(info, "It cannot be found\n");
		}
	}
}

/**
 * fork_cmd - Forks an executing thread to run command.
* @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: void.
 *
 */
void fork_cmd(info_t *info)
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
		if (execve(info->path, info->argv, my_get_environ(info)) == -1)
		{
			my_free_info(info, 1);
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
				error_print(info, "Permission is not allowed\n");
		}
	}
}
