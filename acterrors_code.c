#include "shell.h"

/**
 * _myputs - Prints the input string.
 *
 * @str: The string.
 *
 * Return:  Return nothing.
 *
 */
void _myputs(char *str)
{
	int o = 0;

	if (!str)
		return;
	while (str[o] != '\0')
	{
		_myputchar(str[o]);
		o++;
	}
}

/**
 * _myputchar - Character c is writtenvto stderr.
 *
 * @c: The character.
 *
 * Return: returns1 On success,
 * if an error, -1 is returned, and errno is set appropriately.
 *
 */
int _myputchar(char c)
{
	static char buf[MY_WRITE_BUFFER_SIZE];
static int x;

	if (c == MY_BUFFER_FLUSH || x >= MY_WRITE_BUFFER_SIZE)
	{
	write(2, buf, x);
	x = 0;
	}
	if (c != MY_BUFFER_FLUSH)
	buf[x++] = c;
	return (1);
}

/**
 * _my_putfd - writes the character c to given file descriptor.
 *
 * @c: The character .
 *
 * @fd: The filedescriptor being written to.
 *
 * Return: Return 1 if success, On error, -1 is returned
 * and errno is set appropriately.
 *
 */
int _my_putfd(char c, int fd)
{
	static int x;
	static char buff1[MY_WRITE_BUFFER_SIZE];

	if (c == MY_BUFFER_FLUSH || x >= MY_WRITE_BUFFER_SIZE)
	{
	write(fd, buff1, x);
	x = 0;
	}
	if (c != MY_BUFFER_FLUSH)
	buff1[x++] = c;
	return (1);
}

/**
 * _my_putsfd - Prints the input string.
 * @str: The string.
 *
 * @fd: The file descriptor.
 *
 * Return: The number of chars.
 *
 */
int _my_putsfd(char *str, int fd)
{
	int k = 0;

	if (!str)
	return (0);
	while (*str)
	{
	k += _my_putfd(*str++, fd);
	}
	return (k);
}
