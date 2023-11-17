#include "shell.h"

/**
 * get_history_file - Gets the history file.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: Returns the allocated string containing
 * the history file.
 *
 */

char *get_history_file(info_t *info)
{
	char *dir, *buff;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (my_strlen(dir) + my_strlen(MY_HISTORY_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	my_strcat(buff, "/");
	my_strcat(buff, MY_HISTORY_FILE);
	return (buff);
}

/**
 * _write_history - Create a new file, or append to an
 * an already existing file.
 * @info: The parameter struct.
 *
 * Return: 1 on success, else -1.
 *
 */
int _write_history(info_t *info)
{
	list_t *node = NULL;
	char *nameoffile = get_history_file(info);
	ssize_t fd;

	if (!nameoffile)
	return (-1);

	fd = open(nameoffile, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(nameoffile);
	if (fd == -1)
	return (-1);
	for (node = info->history; node; node = node->nextn)
	{
	__putsfd(node->str, fd);
	_putfd('\n', fd);
	}
	_putfd(MY_BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Reads history from a file.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: history_cnt on success, 0 is returned if not successful.
 *
 */
int read_history(info_t *info)
{
	ssize_t fd, lenofrd, sizeofg = 0;
	struct stat st;
	int h;
int end = 0;
int linecnt = 0;
	char *buff = NULL, *nameoffile = get_history_file(info);

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
			historyBuild_list(info, buff + end, linecnt++);
			end = h + 1;
		}
	if (end != h)
		historyBuild_list(info, buff + end, linecnt++);
	free(buff);
	info->history_cnt = linecnt;
	while (info->history_cnt-- >= MY_HISTORY_MAX)
		remove_index_node(&(info->history), 0);
	my_hist_reassign(info);
	return (info->history_cnt);
}

/**
 * historyBuild_list - Adds entries to a history linked list.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * @buf: buffer.
 * @linecnt: The history linecnt, history_cnt.
 *
 * Return: Always return 0
 *
 */
int historyBuild_list(info_t *info, char *buf, int linecnt)
{
	list_t *myNode = NULL;

	if (info->history)
		myNode = info->history;
	add_end_node(&myNode, buf, linecnt);

	if (!info->history)
		info->history = myNode;
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
