#include "shell.h"

/**
 * handle_line - This function partitions a line read from standard input as
 * needed.
 * @line: The pointer to a line read from standard input.
 * @read: Line length
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void handle_line(char **line, ssize_t read)
{
	char *old_line, *new_line;
	char old, current, next;
	size_t k, l;
	ssize_t new_len;

	new_len = get_new_len(*line);
	if (new_len == read - 1)
		return;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return;
	l = 0;
	old_line = *line;
	for (k = 0; old_line[k]; k++)
	{
		current = old_line[k];
		next = old_line[k + 1];
		if (k != 0)
		{
			old = old_line[k - 1];
			if (current == ';')
			{
				if (next == ';' && old != ' ' && old != ';')
				{
					new_line[l++] = ' ';
					new_line[l++] = ';';
					continue;
				}
				else if (old == ';' && next != ' ')
				{
					new_line[l++] = ';';
					new_line[l++] = ' ';
					continue;
				}
				if (old != ' ')
					new_line[l++] = ' ';
				new_line[l++] = ';';
				if (next != ' ')
					new_line[l++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && old != ' ')
					new_line[l++] = ' ';
				else if (old == '&' && next != ' ')
				{
					new_line[l++] = '&';
					new_line[l++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && old != ' ')
					new_line[l++]  = ' ';
				else if (old == '|' && next != ' ')
				{
					new_line[l++] = '|';
					new_line[l++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (k != 0 && old_line[k - 1] != ' ')
				new_line[l++] = ' ';
			new_line[l++] = ';';
			if (next != ' ' && next != ';')
				new_line[l++] = ' ';
			continue;
		}
		new_line[l++] = old_line[k];
	}
	new_line[l] = '\0';

	free(*line);
	*line = new_line;
}

/**
 * get_new_len -  This function, gets the new length of a line partitioned
 * by ";", "||", "&&&", or "#".
 * @line: The partitioned line to check.
 *
 * Return: New line length.
 *
 * Description: This cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)
{
	size_t k;
	ssize_t new_len = 0;
	char current, next;

	for (k = 0; line[k]; k++)
	{
		current = line[k];
		next = line[k + 1];
		if (current == '#')
		{
			if (k == 0 || line[k - 1] == ' ')
			{
				line[k] = '\0';
				break;
			}
		}
		else if (k != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[k - 1] != ' ' && line[k - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[k - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[k - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				logical_ops(&line[k], &new_len);
		}
		else if (current == ';')
		{
			if (k != 0 && line[k - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}
/**
 * logical_ops - This function checks a line for logical operators "||" or "&&".
 * @line: The pointer to the character to check in the line.
 * @new_len: Pointer to a new_len in get_new_len function.
 */

void logical_ops(char *line, ssize_t *new_len)
{
	char old, current, next;

	old = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && old != ' ')
			(*new_len)++;
		else if (old == '&' && next != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (next == '|' && old != ' ')
			(*new_len)++;
		else if (old == '|' && next != ' ')
			(*new_len)++;
	}
}
