#include "shell.h"

/**
 * main - Entry point of program.
 *
 * @argucount: count of argument.
 *
 * @arguvec: vector of argument.
 *
 *
 * Return: 0 on success, 1 when error.
 *
 */
int main(int argucount, char **arguvec)
{
int fd = 2;
info_t info[] = {INFO_INIT};


	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (argucount == 2)
	{
		fd = open(arguvec[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
			exit(126);
			if (errno == ENOENT)
			{
				_myputs(arguvec[0]);
				_myputs(": 0: File cannot be opened ");
				_myputs(arguvec[1]);
				__eputchar('\n');
				__eputchar(MY_BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hshell(info, arguvec);
	return (EXIT_SUCCESS);
}
