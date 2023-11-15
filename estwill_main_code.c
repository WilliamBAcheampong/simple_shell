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
				_estwillputs(arguvec[0]);
				_estwillputs(": 0: File cannot be opened ");
				_estwillputs(arguvec[1]);
				_estwillputchar('\n');
				_estwillputchar(ESTWILL_BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	estwill_fill_env_list(info);
	estwill_history_read(info);
	hshell(info, arguvec);
	return (EXIT_SUCCESS);
}
