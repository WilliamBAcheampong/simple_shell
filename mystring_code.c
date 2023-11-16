#include "shell.h"

/**
 * my_strlen - Returns len of string.
 *
 * @u: The string.
 *
 * Return: integer len of a string.
 *
 */
int my_strlen(char *u)
{
	int e = 0;

	if (!u)
		return (0);

	while (*u++)
		e++;
	return (e);
}

/**
 * my_strcmp - Performs comparison of two strings.
 * @string1: The 1st string.
 *
 * @string2: The 2nd string.
 *
 * Return: Negative if string1 < string2, zero if string,
 *  positive if string1 > string2 is equal to string 2.
 */
int my_strcmp(char *string2, char *string1)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
		return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
	return (0);
	else
	return (*string1 < *string2 ? -1 : 1);
}

/**
 * my_starts_with - Checks if needle starts with hay.
 * @hay: String to search.
 *
 * @needle: The substring to find or locate.
 *
 * Return: address of next char of hay or NULL.
 *
 */
char *my_starts_with(const char *hay, const char *needle)
{
	while (*needle)
		if (*needle++ != *hay++)
			return (NULL);
	return ((char *)hay);
}

/**
 * my_strcat - Concatenates or combines two strings.
 * @destination: The destination buffer.
 *
 * @source: the source buffer.
 *
 *
 * Return: destination buffer.
 *
 */
char *my_strcat(char *source, char *destination)
{
	char *myret = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (myret);
}
