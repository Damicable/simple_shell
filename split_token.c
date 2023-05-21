#include "shell.h"

char **_strtok(char *line, char *delim);
int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);

/**
 * _strtok - This is a function that tokenizes a string.
 * @line: The string that is to be tokenized.
 * @delim: The delimiter char to be used to tokenize the string.
 *
 * Return: A pointer to tokenized array of words.
 */

char **_strtok(char *line, char *delim)
{
	char **ptr;
	int index = 0, tokens, k, letters, t;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (k = 0; k < tokens; k++)
	{
		while (line[index] == *delim)
			index++;

		letters = token_len(line + index, delim);

		ptr[k] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[k])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (t = 0; t < letters; t++)
		{
			ptr[k][t] = line[index];
			index++;
		}

		ptr[k][t] = '\0';
	}
	ptr[k] = NULL;
	ptr[k + 1] = NULL;

	return (ptr);
}

/**
 * token_len - This function Locates the delimiter index marking the
 * end of the first token contained within a string.
 * @str: The string to be searched through
 * @delim: The delimiter character to search for
 *
 * Return: String pointer, delim length.
 */

int token_len(char *str, char *delim)
{
	int index = 0, len = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		len++;
		index++;

	return (len);
}

/**
 * count_tokens - A function that counts the number of delimite
 * characters contained within a string.
 * @str: The string to search.
 * @delim: The delimiter characters to be counted.
 *
 * Return: The string token.
 */

int count_tokens(char *str, char *delim)
{
	int index, tokens = 0, len = 0;

	for (index = 0; *(str + index); index++)
		len++;

	for (index = 0; index < len; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += token_len(str + index, delim);
		}
	}

	return (tokens);
}
