#include "shell.h"

/**
 * e_atoi - String to integer converter.
 * @s: String that will be converted.
 *
 * Return: if no numbers in string, 0, converted number,
 * if not, -1 when error.
 *
 */
int e_atoi(char *s)
{
	unsigned long int result = 0;
int h = 0;

	if (*s == '+')
		s++;  /* TODO: Why is main returning 255 because of this? */
	for (h = 0;  s[h] != '\0'; h++)
	{
		if (s[h] >= '0' && s[h] <= '9')
		{
			result *= 10;
			result += (s[h] - '0');
			if (result > INT_MAX)
			return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * error_print - Prints an error message
 *
 * @info: Arguments use to maintain function prototypes
 * that are constant are in this structure.
 *
 * @errstr: String containing a specific type of error
 *
 * Return: 0 if no numbers in string, converted number
 * otherwise -1 on error.
 *
 */
void error_print(info_t *info, char *errstr)
{
	_myputs(info->fname);

	_myputs(": ");

	my_print_p(info->errline_cnt, STDERR_FILENO);

	_myputs(": ");

	_myputs(info->argv[0]);

	_myputs(": ");

	_myputs(errstr);
}

/**
 * my_print_p - Function to print decimal number.
 *
 * @input: the input.
 *
 * @fd: the file descriptor being written to.
 *
 * Return: number of characters that are printed.
 *
 */
int my_print_p(int fd, int input)
{
	unsigned int absolute, current;
int (*__putchar)(char) = _putchar;
	int f, cnt = 0;


	if (fd == STDERR_FILENO)
	__putchar = __eputchar;

if (input < 0)
	{
	absolute = -input;
	__putchar('-');
	cnt++;
	}
	else
		absolute = input;
	current = absolute;
	for (f = 1000000000; f > 1; f /= 10)
	{
		if (absolute / f)
		{
		__putchar('0' + current / f);
		cnt++;
		}
		current %= f;
	}
	__putchar('0' + current);
	cnt++;

	return (cnt);
}

/**
 * my_change_num - Function that is a converter,
 * this is a clone of itoa.
 *
 * @numb: number.
 *
 * @baseValue:  base value.
 * @flags: flags of arguments.
 *
 * Return: string.
 *2
 */
char *my_change_num(long int numb, int flags, int baseValue)
{
	char signValue = 0;

static char *array1;

char *ptr;

static char buffer[50];

unsigned long q = numb;

	if (!(flags & TO_UNSIGNED) && numb < 0)
	{
		q = -numb;
		signValue = '-';

	}
	array1 = flags & TO_LOWCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
	*--ptr = array1[q % baseValue];
	q /= baseValue;
	} while (q != 0);

	if (signValue)
	*--ptr = signValue;
	return (ptr);
}

/**
 * delete_comment - function that interchange
 * initial instance of '#' with '\0'.
 *
 * @buf: address of the string being modified.
 *
 * Return: Always 0.
 *
 */
void delete_comment(char *buf)
{
	int a;

		for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
		buf[a] = '\0';
		break;
		}
}
