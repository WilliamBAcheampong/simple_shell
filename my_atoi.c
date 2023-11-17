#include "shell.h"

/**
 * interative - True is returned if shell is in
 * interative mode.
 *
 * @info: address of struct.
 *
 * Return: if interative mode, 1 is returned
 * if not, 0 is returned
 *
 *
 */
int interative(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - delimiter checker.
 * @c: Character to be checked
 *
 * @delimi: The delimiter, which is a string.
 *
 * Return: When True 1 gets returned, 0 rather if False.
 *
 */
int is_delimiter(char c, char *delimi)
{
	while (*delimi)
	if (*delimi++ == c)
		return (1);
	return (0);
}

/**
 * _isalphabet - Alphabetic character checker.
 * @c: Input character.
 *
 * Return: if c is alphabetic 1 is, 0 if c is not.
 *
 */
int _isalphabet(int c)
{
if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	return (1);
	else
	return (0);
}

/**
 * wi_atoi - Used to convert string to integer.
 * @s: The string.
 *
 * Return: returns 0 when no number can be found in the
 * string, converted number if number is found.
 *
 */

int wi_atoi(char *s)
{

unsigned int result = 0;
int v, flag = 0, output, sign = 1;


for (v = 0; s[v] != '\0' && flag != 2; v++)
{
	if (s[v] == '-')
		sign *= -1;

	if (s[v] >= '0' && s[v] <= '9')
	{
		flag = 1;
		result *= 10;
		result += (s[v] - '0');
	}
	else if (flag == 1)
		flag = 2;
}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
