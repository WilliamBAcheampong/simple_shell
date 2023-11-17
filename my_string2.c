#include "shell.h"

/**
 * _strcpy - Copies string.
 *
 * @destination: The destination.
 *
 * @source: The source.
 *
 * Return: destination pointer.
 *
 */
char *_strcpy(char *destination, char *source)
{
	int t = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[t])
	{
		destination[t] = source[t];
		t++;
	}
	destination[t] = 0;
	return (destination);
}

/**
 * _strdup - Duplicates a string.
 *
 * @str: string.
 *
 * Return: Points to the duplicated string.
 *
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *retvalue;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	retvalue = malloc(sizeof(char) * (len + 1));
	if (!retvalue)
		return (NULL);
	for (len++; len--;)
		retvalue[len] = *--str;
	return (retvalue);
}

/**
 * _puts - Prints an input string.
 *
 * @str: The string printed.
 *
 * Return: Nothing.
 *
 */
void _puts(char *str)
{
	int u = 0;

	if (!str)
	return;
	while (str[u] != '\0')
	{
		_putchar(str[u]);
		u++;
	}
}

/**
 * _putchar - Writes the character c to stdout.
 * @c: The character.
 *
 * Return: On success 1.
 *
 * On error, -1 is returned, and errno is set appropriately.
 *
 */
int _putchar(char c)
{
	static char buf[MY_WRITE_BUFFER_SIZE];
	static int e;

	if (c == MY_BUFFER_FLUSH || e >= MY_WRITE_BUFFER_SIZE)
	{
	write(1, buf, e);
	e = 0;
	}
	if (c != MY_BUFFER_FLUSH)
		buf[e++] = c;
	return (1);
}
