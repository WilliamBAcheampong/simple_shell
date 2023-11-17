#include "shell.h"
/**
 * my_exit - Exits the shell.
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
* Return: Exit is returned, together with its status,
 * (0) if info.argv[0] is not equal to ‘exit’.
 *
 */
int my_exit(info_t *info)
{
	int checkexit;

	if (info->argv[1]) /* If there is exit argument */
	{
		checkexit = e_atoi(info->argv[1]);
		if (checkexit == -1)
		{
			info->status = 2;
			error_print(info, "Illegal number: ");
			_myputs(info->argv[1]);
			__eputchar('\n');
			return (1);
		}
		info->err_number = e_atoi(info->argv[1]);
		return (-2);
	}
		info->err_number = -1;
		return (-2);
}

/**
 * my_cd - Process current directory or folder changer.
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: Always returns 0.
 *
 */
int my_cd(info_t *info)
{
char *y, *dir, buffer[1024];
	int ret_chdir;
y = getcwd(buffer, 1024);

	if (!y)
	_puts("TODO: >>getcwd emsg of the failure<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
			if (!dir)
			ret_chdir = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
			else
			ret_chdir = chdir(dir);
	}
			else if (_strcmp(info->argv[1], "-") == 0)
	{
			if (!_getenv(info, "OLDPWD="))
		{
			_puts(y);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		ret_chdir = /* TODO: an idea of of what this would be?? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
	ret_chdir = chdir(info->argv[1]);
	if (ret_chdir == -1)
	{
		error_print(info, "I cannot change directory into");
		_myputs(info->argv[1]), __eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - Current process directory changer.
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *.
 * Return: always 0.
 *
 */
int my_help(info_t *info)
{
	char **my_arg_array;

	my_arg_array = info->argv;
	_puts("Help call. The function can’t be used for now\n");
	if (0)
	_puts(*my_arg_array); /* temp att_unused try and error */
	return (0);
}
