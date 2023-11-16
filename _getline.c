#include "shell.h"

/**
 * input_buffer - buffers chain commands.
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * @buffer: address of buffer.
 * @len: length var’s address.
 *
 * Return: bytes read.
 *
 */
ssize_t input_buffer(info_t *info, char **buffer, size_t *len)
{
	size_t len_p = 0;
ssize_t y = 0;

	if (!*len) /* if buffer is empty, fill it or make it full*/
	{
		/*my_dfree((void **)info->cmd_buffer);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_sigint);
#if USE_GETLINE
		y = getline(buffer, &len_p, stdin);
#else
		y = _my_getline(info, buffer, &len_p);
#endif
		if (y > 0)
		{
			if ((*buffer)[y - 1] == '\n')
			{
				(*buffer)[y - 1] = '\0'; /* newline that trails is cleared*/
				y--;
		}
		info->linecnt_flag = 1;
		delete_comment(*buffer);
		historyBuild_list(info, *buffer, info->history_cnt++);
		/* if (my_strchr(*buffer, ';')) command chain or not? */
		{
				*len = y;
				info->cmd_buffer = buffer;
			}
		}
	}
	return (y);
}

/**
 * my_get_input - This gets a line minus the newline.
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: bytes that is read.
 *
 */
ssize_t my_get_input(info_t *info)
{
	static size_t z, x, len;

static char *buf; /* the ';' command chain buffer */
char **buf_f = &(info->arg), *f;
	ssize_t y = 0;

	my_putchar(MY_BUFFER_FLUSH);
	y = input_buffer(info, &buf, &len);
	if (y == -1) /* EOF */
		return (-1);
	if (len)
	{
		x = z; /* new iterator is initialised to current buffer pos */
		f = buf + z; /* retrieve return pointer */

		my_check_chain(info, buf, &x, z, len);
		while (x < len) /* endofline or semicolon is iterated to */
		{
			if (ischain(info, buf, &x))
				break;
			x++;
		}

		z = x + 1; /* null has been increased past ';'' */
		if (z >= len) /* end of buffer or not? */
		{
			z = len = 0; /* len and pos is resetted */
			info->cmd_buffer_type = MY_COMMAND_NORM;
		}

		*buf_f = f; /* back pointer is passed to current command pos */
		return (my_strlen(f)); /* len of current command is returned */
	}

	*buf_f = buf; /* else not a chain, pass back buffer from _my_getline() */
	return (y); /* return len of buffer from _my_getline() */
}

/**
 * read_buf - Buffer reader.
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * @buf: buffer.
 * @b: size.
 *
 * Return: y.
 *
 */
ssize_t read_buf(info_t *info, size_t *b, char *buf)
{
	ssize_t y = 0;

	if (*b)
		return (0);
	y = read(info->readfd, buf, MY_READ_BUFFER_SIZE);
	if (y >= 0)
		*b = y;
	return (y);
}

/**
 * _my_getline - This gets the next line of input from STDIN.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * @pointer: Address of pointer to buffer, preallocated or NULL.
 * @len: Size of preallocated pointer buffer if not NULL.
 *
 * Return: s.
 *
 */
int _my_getline(info_t *info, char **pointer, size_t *len)
{
	static char buf[MY_READ_BUFFER_SIZE];
	size_t q;
static size_t d, length;
	char *f = NULL, *new_f = NULL, *v;
	ssize_t y = 0, u = 0;

	f = *pointer;
	if (f && len)
		u = *len;
	if (d == length)
		d = length = 0;

	y = read_buf(info, &length, buf);
	if (y == -1 || (u == 0 && length == 0))
		return (-1);

	v = my_strchr(buf + d, '\n');
	q = v ? 1 + (unsigned int)(v - buf) : length;
	new_f = _realloc(f, u, u ? u + q : q + 1);
	if (!new_f) /* MALLOC FAILURE! */
		return (f ? free(f), -1 : -1);

	if (u)
		my_strncat(new_f, buf + d, q - d);
	else
		_strncpy(new_f, buf + d, q - d + 1);

	u += q - d;
	d = q;
	f = new_f;
	if (len)
	*len = u;
	*pointer = f;
	return (u);
}
/**
 * handle_sigint - blocks ctrl-C.
 *
 * @signalNumber: the signal number.
 *
 * Return: void.
 *
 */
void handle_sigint(__attribute__((unused))int signalNumber)
{
	_willputs("\n");

	_willputs("$ ");

	my_putchar(MY_BUFFER_FLUSH);
}
