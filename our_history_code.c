#include "shell.h"

/**
 * estwill_get_history_file- Gets the history file.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: Returns the allocated string containing
 * the history file.
 *
 */

char *estwill_get_history_file(info_t *info)
{
	char *dir, *buff;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (estwill_strlen(dir) + estwill_strlen(ESTWILL_HISTORY_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	estwill_strcpy(buff, dir);
	estwill_strcat(buff, "/");
	estwill_strcat(buff, ESTWILL_HISTORY_FILE);
	return (buff);
}

/**
 * estwill_hist_record - Create a new file, or append to an
 * an already existing file.
 * @info: The parameter struct.
 *
 * Return: 1 on success, else -1.
 *
 */
int estwill_hist_record(info_t *info)
{
	list_t *node = NULL;
	char *nameoffile = estwill_get_history_file(info);
	ssize_t fd;

	if (!nameoffile)
	return (-1);

	fd = open(nameoffile, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(nameoffile);
	if (fd == -1)
	return (-1);
	for (node = info->history; node; node = node->nextn)
	{
	_estwillputsfd(node->str, fd);
	_estwillputfd('\n', fd);
	}
	_estwillputfd(ESTWILL_BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * estwill_history_read - Reads history from a file.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: history_cnt on success, 0 is returned if not successful.
 *
 */
int estwill_history_read(info_t *info)
{
	ssize_t fd, lenofrd, sizeofg = 0;
	struct stat st;
	int h;
int end = 0;
int linecnt = 0;
	char *buff = NULL, *nameoffile = estwill_get_history_file(info);

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
			estwill_hist_construct_list(info, buff + end, linecnt++);
			end = h + 1;
		}
	if (end != h)
		estwill_hist_construct_list(info, buff + end, linecnt++);
	free(buff);
	info->history_cnt = linecnt;
	while (info->history_cnt-- >= ESTWILL_HISTORY_MAX)
		estwill_remove_index_node(&(info->history), 0);
	estwill_hist_reassign(info);
	return (info->history_cnt);
}

/**
 * estwill_hist_construct_list - Adds entries to a history linked list.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * @buffer: buffer.
 * @linecnt: The history linecnt, history_cnt.
 *
 * Return: 0.
 *
 */
int estwill_hist_construct_list(info_t *info, char *buffer, int linecnt)
{
	list_t *mynode = NULL;

	if (info->history)
		mynode = info->history;
	estwill_add_node_at_end(&mynode, buffer, linecnt);

	if (!info->history)
		info->history = mynode;
	return (0);
}

/**
 * estwill_hist_reassign - Reallocates numbers to the history
 * linked list after changes.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 * Return: New history_cnt.
 *
 */
int estwill_hist_reassign(info_t *info)
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
