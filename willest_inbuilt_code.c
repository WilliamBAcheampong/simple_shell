#include "shell.h"
/**
 * estwill_exit - Exits the shell.
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
* Return: Exit is returned, together with its status,
 * (0) if info.argv[0] is not equal to ‘exit’.
 *
 */
int estwill_exit(info_t *info)
{
	int checkingexit;

	if (info->argv[1]) /* If there is exit argument */
	{
		checkingexit = est_atoi(info->argv[1]);
		if (checkingexit == -1)
		{
			info->status = 2;
			estwill_errorPrint(info, "Illegal number: ");
			_estwillputs(info->argv[1]);
			_estwillputchar('\n');
			return (1);
		}
		info->errcode_numb = est_atoi(info->argv[1]);
		return (-2);
	}
		info->errcode_numb = -1;
		return (-2);
}

/**
 * estwill_mcd - Process current directory or folder changer,
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: Always returns 0.
 *
 */
int estwill_mcd(info_t *info)
{
buffer[1024] char *y, *dir;
	int ret_chdir;
s = getcwd(buffer, 1024);

	if (!s)
	_estwillputs("TODO: >>getcwd emsg of the failure<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
			if (!dir)
			ret_chdir = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
			else
			ret_chdir = chdir(dir);
	}
	else if (estwill_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_estwillputs(s);
			estwill_putchar('\n');
			return (1);
		}
		_estwillputs(_getenv(info, "OLDPWD=")), estwill_putchar('\n');
		ret_chdir = /* TODO: an idea of of what this would be?? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
	ret_chdir = chdir(info->argv[1]);
	if (ret_chdir == -1)
	{
		estwill_errorPrint(info, ‘I cannot change directory into ‘);
		_estwillputs(info->argv[1]), _estwillputchar('\n');
	}
	else
	{
		estwill_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		estwill_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * estwill_help - Current process directory changer.
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *.
 * Return: always 0.
 *
 */
int estwill_help(info_t *info)
{
	char **my_arg_array;

	my_arg_array = info->argv;
	_estwillputs("Help call. The function can’t be used for now\n");
	if (0)
	_estwillputs(*my_arg_array); /* temp att_unused try and error */
	return (0);
}
