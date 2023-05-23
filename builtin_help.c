#include "shell.h"

/**
 * get_builtin - This program matches a command with a corresponding
 * shellby builtin function.
 * @command: A command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */

int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", shellby_exit },
		{ "env", shellby_env },
		{ "setenv", shellby_setenv },
		{ "unsetenv", shellby_unsetenv },
		{ "cd", shellby_cd },
		{ "alias", shellby_alias },
		{ "help", shellby_help },
		{ NULL, NULL }
	};
	int k;

	for (k = 0; funcs[k].name; k++)
	{
		if (_strcmp(funcs[k].name, command) == 0)
			break;
	}
	return (funcs[k].f);
}

/**
 * shellby_cd - This file changes the current directory of the shellby
 * process.
 * @args: An array of arguments passed
 * @front: A double pointer to the beginning of arguments
 *
 * Return: -2 if the given string is not a directory, - 1 if an error
 * occur, otherwise 0.
 */

int shellby_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_details, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_details = malloc(sizeof(char *) * 2);
	if (!dir_details)
		return (-1);

	dir_details[0] = "OLDPWD";
	dir_details[1] = oldpwd;
	if (shellby_setenv(dir_details, dir_details) == -1)
		return (-1);

	dir_details[0] = "PWD";
	dir_details[1] = pwd;
	if (shellby_setenv(dir_details, dir_details) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_details);
	return (0);
}

/**
 * shellby_help - This program displays information about shellby
 * builtin commands.
 * @args: An array of arguments passed.
 * @front: Pointer to the beginning of argument.
 *
 * Return: -1 if an error occurs,otherwise - 0.
 */

int shellby_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}

/**
 * shellby_exit - This program terminates the normal shellby shell process.
 * @args: An array of arguments containing the exit value.
 * @front: Double pointer to the beginning of arguments.
 *
 * Return: -3 if no arguments, -2 if the given exit value is invalid
 * otherwise - exits with the given status value.
 *
 * Description: After returning -3, the program exits back in the main function.
 */

int shellby_exit(char **args, char **front)
{
	int k, int_len = 10;
	unsigned int sum = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			k = 1;
			int_len++;
		}
		for (; args[0][k]; k++)
		{
			if (k <= int && args[0][k] >= '0' && args[0][k] <= '9')
				sum = (sum * 10) + (args[0][k] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (sum > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_args(args, front);
	free_env();
	free_alias_list(aliases);
	exit(sum);
}
