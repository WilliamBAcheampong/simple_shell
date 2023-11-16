#include "shell.h"

/**
 * my_get_history_file- Gets the history file.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: Returns the allocated string containing
 * the history file.
 *
 */

char *my_get_history_file(info_t *info)
{
	char *dir, *buff;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (my_strlen(dir) + my_strlen(MY_HISTORY_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	my_strcpy(buff, dir);
	my_strcat(buff, "/");
	my_strcat(buff, MY_HISTORY_FILE);
	return (buff);
}

/**
 * my_hist_record - Create a new file, or append to an
 * an already existing file.
 * @info: The parameter struct.
 *
 * Return: 1 on success, else -1.
 *
 */
int my_hist_record(info_t *info)
{
	list_t *node = NULL;
	char *nameoffile = my_get_history_file(info);
	ssize_t fd;

	if (!nameoffile)
	return (-1);

	fd = open(nameoffile, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(nameoffile);
	if (fd == -1)
	return (-1);
	for (node = info->history; node; node = node->nextn)
	{
	_myputsfd(node->str, fd);
	_myputfd('\n', fd);
	}
	_myputfd(MY_BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * my_history_read - Reads history from a file.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: history_cnt on success, 0 is returned if not successful.
 *
 */
int my_history_read(info_t *info)
{
	ssize_t fd, lenofrd, sizeofg = 0;
	struct stat st;
	int h;
int end = 0;
int linecnt = 0;
	char *buff = NULL, *nameoffile = my_get_history_file(info);

	if (!nameoffile)
		return (0);
	fd = open(nameoffile, O_RDONLY);
	free(nameoffile);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		sizeofg = st.st_size;
	if (sizeofg < 2)
		return (0);
	buff = malloc(sizeof(char) * (sizeofg + 1));
	if (!buff)
		return (0);
	lenofrd = read(fd, buff, sizeofg);
	buff[sizeofg] = 0;
	if (lenofrd <= 0)
		return (free(buff), 0);
	close(fd);
	for (h = 0; h < sizeofg; h++)
		if (buff[h] == '\n')
		{
			buff[h] = 0;
			my_hist_construct_list(info, buff + end, linecnt++);
			end = h + 1;
		}
	if (end != h)
		my_hist_construct_list(info, buff + end, linecnt++);
	free(buff);
	info->history_cnt = linecnt;
	while (info->history_cnt-- >= MY_HISTORY_MAX)
		my_remove_index_node(&(info->history), 0);
	my_hist_reassign(info);
	return (info->history_cnt);
}

/**
 * my_hist_construct_list - Adds entries to a history linked list.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * @buffer: buffer.
 * @linecnt: The history linecnt, history_cnt.
 *
 * Return: 0.
 *
 */
int my_hist_construct_list(info_t *info, char *buffer, int linecnt)
{
	list_t *mynode = NULL;

	if (info->history)
		mynode = info->history;
	my_add_node_at_end(&mynode, buffer, linecnt);

	if (!info->history)
		info->history = mynode;
	return (0);
}

/**
 * my_hist_reassign - Reallocates numbers to the history
 * linked list after changes.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 * Return: New history_cnt.
 *
 */
int my_hist_reassign(info_t *info)
{
int e = 0;
list_t *node = info->history;


	while (node)
	{
		node->numb = e++;
		node = node->nextn;
	}
	return (info->history_cnt = e);
}
