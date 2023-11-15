#include "shell.h"

/**
 * **estwill_strtok - Divide a string into words,
 * repeated delimiters are ignored.
 * @str: the input string.
 *
 * @z: the delimiter string.
 * Return: pointer to an array of strings,
 * or NULL if failure.
 *
 */

char **estwill_strtok(char *str, char *z)
{
int a, m;
int x;
int k;
int numbwords = 0;
	char **h;

	if (str == NULL || str[0] == 0)
		return (NULL);

	if (!z)
		z = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delimi(str[a], z) && (is_delimi(str[a + 1], z) || !str[a + 1]))
			numbwords++;
	if (numbwords == 0)
		return (NULL);
	h = malloc((1 + numbwords) * sizeof(char *));
	if (!h)
		return (NULL);
	for (x = 0, a = 0; x < numbwords; x++)
	{
		while (is_delimi(str[a], z))
			a++;
		k = 0;
		while (!is_delimi(str[a + k], z) && str[a + k])
			k++;
		h[x] = malloc((k + 1) * sizeof(char));
		if (!h[x])
		{
			for (k = 0; k < x; k++)
				free(h[k]);
			free(h);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			h[x][m] = str[a++];
		h[x][m] = 0;
	}
	h[x] = NULL;
	return (h);
}

/**
 * **estwill_strtok1 - Divide string into words.
 *
 * @str: the string inputted.
 *
 * @w: delimiter.
 * Return: a pointer to an array of strings,
 * or NULL on failure.
 *
 */
char **estwill_strtok1(char *str, char w)
{
	int e, r, u, f, numbwords = 0;
	char **v;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (e = 0; str[e] != '\0'; e++)
		if ((str[e] != w && str[e + 1] == w) ||
				    (str[e] != w && !str[e + 1]) || str[e + 1] == w)
			numbwords++;
	if (numbwords == 0)
		return (NULL);
	v = malloc((1 + numbwords) * sizeof(char *));
	if (!v)
		return (NULL);
	for (r = 0, e = 0; r < numbwords; r++)
	{
		while (str[e] == w && str[e] != w)
			e++;
		u = 0;
		while (str[e + u] != w && str[e + u] && str[e + u] != w)
			u++;
		v[r] = malloc((u + 1) * sizeof(char));
		if (!v[r])
		{
			for (u = 0; u < r; u++)
				free(v[u]);
			free(v);
			return (NULL);
		}
		for (f = 0; f < u; f++)
			v[r][f] = str[e++];
		v[r][f] = 0;
	}
	v[r] = NULL;
	return (v);
}
