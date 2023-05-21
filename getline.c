#include "shell.h"

/**
 * _getline - This is a function that reads input from a stream.
 * @lineptr: A buffer that stores the input.
 * @n: The size of lineptr.
 * @stream: The stream to read  input from.
 *
 * Return: The read number of bytes from th stream
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int k;

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
		k = read(STDIN_FILENO, &c, 1);
		if (k == -1 || (k == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (k == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	assign_lineptr(lineptr, n, buffer, input);
	ret = input;
	if (k != 0)
		input = 0;
	return (ret);
}

/**
 * _realloc - This is a function that reallocates a memory block using
 * malloc and free.
 * @ptr: Its a pointer to the already allocated memory
 * @old_size: The size in bytes of the old memory for ptr.
 * @new_size: The bytes size for the new memory block.
 *
 * Return: ptr if new_size == old_size, NULL if new_size == 0
 * and ptr is not NULL, Otherwise - a pointer to the new memory block.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *buf;
	char *ptr_copy, *memory;
	unsigned int index;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		buf = malloc(new_size);
		if (buf == NULL)
			return (NULL);

		return (buf);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	buf = malloc(sizeof(*ptr_copy) * new_size);
	if (buf == NULL)
	{
		free(ptr);
		return (NULL);
	}

	memory = buf;

	for (index = 0; index < old_size && index < new_size; index++)
		memory[index] = *ptr_copy++;

	free(ptr);
	return (buf);
}

/**
 * assign_lineptr - This function, reassigns the lineptr variable
 * for _getline.
 * @lineptr: A buffer space to store an input string.
 * @n: Size of the lineptr.
 * @buffer: The space to assign to lineptr.
 * @b: Buffer size.
 */

void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);

	}
}
