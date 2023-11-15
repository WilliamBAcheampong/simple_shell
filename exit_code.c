#include "shell.h"

/**
 *estwill_strncpy - Copy a string.
 *
 *@destination: The destination of the copied string.
 *
 *@src: The source string.
 *@t: The total of characters to copy.
 *Return: Concatenated string.
 *
 */
char *estwill_strncpy(char *destination, char *src, int t)
{
	int f, g;
	char *s = destination;

	f = 0;
	while (src[f] != '\0' && f < t - 1)
	{
		destination[f] = src[f];
		f++;
	}
	if (f < t)
	{
		g = f;
		while (g < t)
		{
			destination[g] = '\0';
			g++;
		}
	}
	return (s);
}

/**
 *estwill_strncat - this concatenates two strings.
 *
 *@destination: The 1st string.
 *@src: The 2nd string.
 *
 *@t: The amount of bytes to be fully used.
 *
 *Return: the concatenated string.
 *
 */
char *estwill_strncat(char *destination, char *src, int t)
{
	int f, g;
	char *s = destination;

	f = 0;
	g = 0;
	while (destination[f] != '\0')
		f++;
	while (src[g] != '\0' && g < t)
	{
		destination[f] = src[g];
		f++;
		g++;
	}
	if (g < t)
		destination[f] = '\0';
	return (s);
}

/**
 *estwill_strchr - Locator of a character in a string.
 *@s: The string that will be parsed.
 *
 *@c: The character we want.
 *
 *Return: Return s, a pointer to the memory area s.
 *
 */
char *estwill_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
