#include "shell.h"

/**
 * _estwillputs - Prints the input string.
 *
 * @str: The string.
 *
 * Return:  Return nothing.
 *
 */
void _estwillputs(char *str)
{
	int o = 0;

	if (!str)
		return;
	while (str[o] != '\0')
	{
		_estwillputchar(str[o]);
		o++;
	}
}

/**
 * _estwillputchar - Character c is writtenvto stderr.
 *
 * @c: The character.
 *
 * Return: returns1 On success,
 * if an error, -1 is returned, and errno is set appropriately.
 *
 */
int _estwillputchar(char c)
{
	static char buf[ESTWILL_WRITE_BUFFER_SIZE];
static int x;

	if (c == ESTWILL_BUFFER_FLUSH || x >= ESTWILL_WRITE_BUFFER_SIZE)
	{
	write(2, buf, x);
	x = 0;
	}
	if (c != ESTWILL_BUFFER_FLUSH)
	buf[x++] = c;
	return (1);
}

/**
 * _estwillputfd - writes the character c to given file descriptor.
 *
 * @c: The character .
 *
 * @fd: The filedescriptor being written to.
 *
 * Return: Return 1 if success, On error, -1 is returned
 * and errno is set appropriately.
 *
 */
int _estwillputfd(int fd, char c)
{
	static int x;
	static char buff1[ESTWILL_WRITE_BUFFER_SIZE];

	if (c == ESTWILL_BUFFER_FLUSH || x >= ESTWILL_WRITE_BUFFER_SIZE)
	{
	write(fd, buff1, x);
	x = 0;
	}
	if (c != ESTWILL_BUFFER_FLUSH)
	buff1[x++] = c;
	return (1);
}

/**
 * _estwillputsfd - Prints the input string.
 * @str: The string.
 *
 * @fd: The file descriptor.
 *
 * Return: The number of chars.
 *
 */
int _estwillputsfd(char *str, int fd)
{
	int k = 0;

	if (!str)
	return (0);
	while (*str)
	{
	k += _estwillputfd(*str++, fd);
	}
	return (k);
}
