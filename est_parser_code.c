#include "shell.h"

/**
 * estwill_is_cmd - Determines whether a file can be executed as
 * a command
 *
 * @info: The info struct.
 *
 *
 * @path: Path to locate file.
 *
 * Return: if true 1, 0 if false.
 *
 */
int estwill_is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * estwill_dupli_chars - duplicates characters.
 * @string_path: The path string
 * @start_index: Beginning index.
 *
 * @stop_index: Ending index.
 *
 * Return: pointer to new buffer.
 *
 */
char *estwill_dupli_chars(char *string_path, int stop_index, int start_index)
{
	int d = 0;
	static char buffer[1024];
	int g = 0;

	for (g = 0, d = start_index; d < stop_index; d++)
		if (string_path[d] != ':')
			buffer[g++] = string_path[d];
	buffer[g] = 0;
	return (buffer);
}

/**
 * estwill_get_path - Finds this cmd in the PATH string.
 * @info: The info struct.
 *
 * @string_path: The PATH string.
 * @command: The command to find.
 *
 * Return: full path of command if found or NULL.
 *
 */
char *estwill_get_path(info_t *info, char *command, char *string_path)
{
	int p = 0, cur_posi = 0;
	char *path12;

	if (!string_path)
		return (NULL);
	if ((estwill_strlen(command) > 2) && estwill_starts_with(command, "./"))
	{
		if (estwill_is_cmd(info, command))
			return (command);
	}
	while (1)
	{
		if (!string_path[p] || string_path[p] == ':')
		{
			path12 = estwill_dupli_chars(string_path, cur_posi, p);
			if (!*path12)
				estwill_strcat(path12, command);
			else
			{
				estwill_strcat(path12, "/");
				estwill_strcat(path12, command);
			}
			if (estwill_is_cmd(info, path12))
				return (path12);
			if (!string_path[p])
				break;
			cur_posi = p;
		}
		p++;
	}
	return (NULL);
}
