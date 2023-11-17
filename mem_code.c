#include "shell.h"

/**
 * my_dfree - Frees a pointer and make
 * address of the pointer null.
 *
 * @pointer: address of the pointer to be freed.
 *
 *
 * Return: if freed 1, 0 if not freed
 *
 */

int my_dfree(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
return (0);
}
