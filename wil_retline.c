#include "shell.h"

/**
 * input_buf - buffers chain commands.
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
ssize_t input_buf(info_t *info, char **buffer, size_t *len)
{
	size_t len_p = 0;
ssize_t y = 0;

	if (!*len) /* if buffer is empty, fill it or make it full*/
	{
		/*estwill_dfree((void **)info->cmd_buffer);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, estwill_handle_sigint);
#if ESTWILL_GET_LINE
		y = getline(buffer, &len_p, stdin);
#else
		y = estwill_get_line(info, bufbuffer, &len_p);
#endif
		if (y > 0)
		{
			if ((*buffer)[y - 1] == '\n')
			{
				(*buffer)[y - 1] = '\0'; /* newline that trails is cleared*/
				y--;
		}
		info->linecnt_flag = 1;
		estwill_delete_comment(*buffer);
		estwill_hist_construct_list(info, *buffer, info->history_cnt++);
		/* if (estwill_strchr(*buffer, ';')) command chain or not? */
		{
				*len = y;
				info->cmd_buffer = buffer;
			}
		}
	}
	return (y);
}

/**
 * estwill_get_input - This gets a line minus the newline.
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * Return: bytes that is read.
 *
 */
ssize_t estwill_get_input(info_t *info)
{
	static size_t z, x, len;

static char *buf; /* the ';' command chain buffer */
char **buf_f = &(info->arg), *f;
	ssize_t y = 0;

	estwill_putchar(ESTWILL_BUFFER_FLUSH);
	y = input_buf(info, &buf, &len);
	if (y == -1) /* EOF */
		return (-1);
	if (len)
	{
		x = z; /* new iterator is initialised to current buffer pos */
		f = buf + z; /* retrieve return pointer */

		estwill_check_chain(info, buf, &x, z, len);
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
			info->cmd_buffer_type = ESTWILL_COMMAND_NORM;
		}

		*buf_f = f; /* back pointer is passed to current command pos */
		return (estwill_strlen(f)); /* len of current command is returned */
	}

	*buf_f = buf; /* else not a chain, pass back buffer from estwill_get_line() */
	return (y); /* return len of buffer from estwill_get_line() */
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
	y = read(info->readfd, buf, ESTWILL_READ_BUFFER_SIZE);
	if (y >= 0)
		*b = y;
	return (y);
}

/**
 * estwill_get_line - This gets the next line of input from STDIN.
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * @pointer: Address of pointer to buffer, preallocated or NULL.
 * @len: Size of preallocated pointer buffer if not NULL.
 *
 * Return: s.
 *
 */
int estwill_get_line(info_t *info, char **pointer, size_t *len)
{
	static char buf[ESTWILL_READ_BUFFER_SIZE];
	size_t q;
static size_t d, length;
	char *f = NULL, *new_f = NULL, *v;
	ssize_t y = 0, u = 0;

	f = *pointer;
	if (f && len)
		u = *len;
	if (d == length)
		d = length = 0;

	y = read_buf(info, buf, &length);
	if (y == -1 || (u == 0 && length == 0))
		return (-1);

	v = estwill_strchr(buf + d, '\n');
	q = v ? 1 + (unsigned int)(v - buf) : length;
	new_f = _realloc(f, u, u ? u + q : q + 1);
	if (!new_f) /* MALLOC FAILURE! */
		return (f ? free(f), -1 : -1);

	if (s)
		estwill_strncat(new_f, buf + d, q - d);
	else
		estwill_strncpy(new_f, buf + d, q - d + 1);

	u += q - d;
	d = q;
	f = new_f;
	if (len)
	*len = u;
	*pointer = f;
	return (u);
}
/**
 * estwill_handle_sigint - blocks ctrl-C.
 *
 * @sig_numb: the signal number.
 *
 * Return: void.
 *
 */
void estwill_handle_sigint(__attribute__((unused))int sig_numb)
{
	_estwillputs("\n");

	_estwillputs("$ ");

	estwill_putchar(ESTWILL_BUFFER_FLUSH);
}
