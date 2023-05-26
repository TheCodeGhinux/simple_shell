#include "shell.h"

void *re_alloc(void *prev, unsigned int old_size, unsigned int new_size);
void assign_lineprev(char **lineprev, size_t *n, char *buffer, size_t b);
ssize_t get_line(char **lineprev, size_t *n, FILE *stream);

/**
 * re_alloc - Reallocates a memory block using malloc and free.
 * @prev: A pointer to the memory previously allocated.
 * @old_size: The size in bytes of the allocated space for prev.
 * @new_size: The size in bytes for the new memory block.
 *
 * Return: If new_size == old_size - prev.
 *         If new_size == 0 and prev is not NULL - NULL.
 *         Else - a pointer to the reallocated memory block.
 */
void *re_alloc(void *prev, unsigned int old_size, unsigned int new_size)
{
	void *memory;
	char *prev_copy, *filler;
	unsigned int i;

	if (new_size == old_size)
		return (prev);

	if (prev == NULL)
	{
		memory = malloc(new_size);
		if (memory == NULL)
			return (NULL);

		return (memory);
	}

	if (new_size == 0 && prev != NULL)
	{
		free(prev);
		return (NULL);
	}

	prev_copy = prev;
	memory = malloc(sizeof(*prev_copy) * new_size);
	if (memory == NULL)
	{
		free(prev);
		return (NULL);
	}

	filler = memory;

	for (i = 0; i < old_size && i < new_size; i++)
		filler[i] = *prev_copy++;

	free(prev);
	return (memory);
}

/**
 * assign_lineprev - Reassigns the lineprev variable for get_line.
 * @lineprev: A buffer to store an input string.
 * @n: The size of lineprev.
 * @buffer: The string to assign to lineprev.
 * @b: The size of buffer.
 */
void assign_lineprev(char **lineprev, size_t *n, char *buffer, size_t b)
{
	if (*lineprev == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineprev = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineprev = buffer;
	}
	else
	{
		_strcpy(*lineprev, buffer);
		free(buffer);
	}
}

/**
 * get_line - Reads input from a stream.
 * @lineprev: A buffer to store the input.
 * @n: The size of lineprev.
 * @stream: The stream to read from.
 *
 * Return: The number of bytes read.
 */
ssize_t get_line(char **lineprev, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = re_alloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	assign_lineprev(lineprev, n, buffer, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}
