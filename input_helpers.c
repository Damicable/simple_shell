#include "shell.h"

/**
 * get_args - This is a function that gets a command from standard input.
 * @line: A buffer to store the command.
 * @exe_ret: The return value of last executed command.
 *
 * Return: NULL if an error occurs, Otherwise - pointer to the stored command.
 */

char *get_args(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read);

	return (line);
}

/**
 * call_args - This function seperates operators from commands and calls them.
 * @args: An array of arguments.
 * @front: Double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: Last executed command retured value
 */

int call_args(char **args, char **front, int *exe_ret)
{
	int ret, index;

	if (!args[0])
		return (*exe_ret);
	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
		else if (_strncmp(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
	}
	args = replace_aliases(args);
	ret = run_args(args, front, exe_ret);
	return (ret);
}

/**
 * run_args - This functions calls the execution of a command.
 * @args: An array of arguments.
 * @front: Double pointer to the beginning of argument.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: Last executed command's returned value.
 */

int run_args(char **args, char **front, int *exe_ret)
{
	int ret, k;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(args, front);
		ret = *exe_ret;
	}

	hist++;

	for (k = 0; args[k]; k++)
		free(args[k]);

	return (ret);
}

/**
 * handle_args - This function gets, calls, and runs the execution of a
 * command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: -2 if an end-of-file is read - END_OF_FILE. -1 if input can't be
 *tokenized,Otherwise - last executed command value.
 */

int handle_args(int *exe_ret)
{
	int ret = 0, index;
	char **args, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * check_args - This function checks if there are any
 * leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to the tokenized commands and arguments.
 *
 * Return: -2, if a ';', '&&', or '||' is placed at an invalid position,
 * Otherwise - 0.
 */

int check_args(char **args)
{
	size_t k;
	char *current, *next;

	for (k = 0; args[k]; k++)
	{
		current = args[k];
		if (current[0] == ';' || current[0] == '&' || current[0] == '|')
		{
			if (k == 0 || current[1] == ';')
				return (create_error(&args[k], 2));
			next = args[k + 1];
			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
				return (create_error(&args[k + 1], 2));
		}
	}
	return (0);
}
