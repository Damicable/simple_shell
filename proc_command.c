#include "shell.h"

/**
 * cant_open - A function that prints a can't open error of a file
 * that doesn't exist or lacks proper permissions
 * @file_path: Path to the file that can't open
 *
 * Return: 127.
 */

int cant_open(char *file_path)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (127);

	len = _strlen(name) + _strlen(hist_str) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * proc_file_commands - write a function that takes a file and
 * attempts to run the commands stored in it
 * @file_path: Path to the file.
 * @exe_ret: Last executed command value returned.
 *
 * Return: 127 if file can not be opened, -1 if malloc fails,
 * Otherwise the return value of the last command ran.
 */

int proc_file_commands(char *file_path, int *exe_ret)
{
	ssize_t file, o_read, k;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		o_read = read(file, buffer, 119);
		if (o_read == 0 && line_size == 0)
			return (*exe_ret);
		buffer[o_read] = '\0';
		line_size += o_read;
		line = _realloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	} while (o_read);
	for (k = 0; line[k] == '\n'; k++)
		line[k] = ' ';
	for (; k < line_size; k++)
	{
		if (line[k] == '\n')
		{
			line[k] = ';';
			for (k += 1; k < line_size && line[k] == '\n'; k++)
				line[k] = ' ';
		}
	}
	variable_replacement(&line, exe_ret);
	handle_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;
	for (k = 0; args[k]; k++)
	{
		if (_strncmp(args[k], ";", 1) == 0)
		{
			free(args[k]);
			args[k] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++k];
			k = 0;
		}
	}
	ret = call_args(args, front, exe_ret);
	free(front);
	return (ret);
}
