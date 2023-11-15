#include "shell.h"

/**
 * estwill_setmemory - Fills memory with a constant byte.
 * @a: Memory area pointer.
 * @t: The byte that *s is fill with.
 *
 * @f: The amount of bytes to be filled.
 * Return: pointer to the memory area s, (s).
 *
 */
char *estwill_setmemory(char *a, char t, unsigned int f)
{
	unsigned int m;

	for (m = 0; m < f; m++)
		a[m] = t;
	return (a);
}

/**
 * estwill_jfree - Frees a string of strings.
 * @ee: String of strings
 */
void estwill_jfree(char **ee)
{
	char **y = ee;

	if (!ee)
		return;
	while (*ee)
		free(*ee++);
	free(y);
}

/**
 * _realloc - Reallocates block of memory.
 *
 *
 * @prvblk: Point to the previous mallocated block.
 * @unused_blk: previous block byte size.
 *
 * @newblk: new block byte size.
 *
 * Return: pointer to.
 */
void *_realloc(void *prvblk, unsigned int unused_blk, unsigned int newblk)
{
	char *f;

	if (!prvblk)
		return (malloc(newblk));
	if (!newblk)
	return (free(prvblk), NULL);
	if (newblk == unused_blk)
		return (prvblk);

	f = malloc(newblk);
	if (!f)
	return (NULL);

	unused_blk = unused_blk < newblk ? unused_blk : newblk;
	while (unused_blk--)
		f[unused_blk] = ((char *)prvblk)[unused_blk];
	free(prvblk);
	return (f);
}
