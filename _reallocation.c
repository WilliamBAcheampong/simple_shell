#include "shell.h"

/**
 * my_setmemory - Fills memory with a constant byte.
 * @a: Memory area pointer.
 * @t: The byte that *s is fill with.
 *
 * @f: The amount of bytes to be filled.
 * Return: pointer to the memory area s, (s).
 *
 */
char *my_setmemory(char *a, char t, unsigned int f)
{
	unsigned int m;

	for (m = 0; m < f; m++)
		a[m] = t;
	return (a);
}

/**
 * my_jfree - Frees a string of strings.
 * @ee: String of strings
 */
void my_jfree(char **ee)
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
 * @pointer: Point to the previous mallocated block.
 * @_oldSize: previous block byte size.
 *
 * @_newSize: new block byte size.
 *
 * Return: pointer to.
 */
void *_realloc(void *pointer, unsigned int _oldSize, unsigned int _newSize)
{
	char *f;

	if (!pointer)
		return (malloc(_newSize));
	if (!_newSize)
	return (free(pointer), NULL);
	if (_newSize == _oldSize)
		return (pointer);

	f = malloc(_newSize);
	if (!f)
	return (NULL);

	_oldSize = _oldSize < _newSize ? _oldSize : _newSize;
	while (_oldSize--)
		f[_oldSize] = ((char *)pointer)[_oldSize];
	free(pointer);
	return (f);
}
