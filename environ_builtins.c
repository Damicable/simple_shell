#include "shell.h"

int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_env - This function prints the current environment.
 * @args: An array of arguments passed to the shell.
 * @front: Double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1, Otherwise - 0.
 *
 * Description: This prints one variable per line in the
 *              format 'variable'='value'.
 */
int shellby_env(char **args, char __attribute__((__unused__)) **front)
{
	int index;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * shellby_setenv - This functin changes or adds an environmental variable
 * to the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the name of the current or existing PATH variable
 *              args[2] is the value to set the current variable to.
 *
 * Return: -1 if an error occur, otherwise 0
 */

int shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **current_environ, *current_value;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	current_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!current_value)
		return (create_error(args, -1));
	_strcpy(current_value, args[0]);
	_strcat(current_value, "=");
	_strcat(current_value, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = current_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	current_environ = malloc(sizeof(char *) * (size + 2));
	if (!current_environ)
	{
		free(current_value);
		return (create_error(args, -1));
	}

	for (index = 0; environ[index]; index++)
		current_environ[index] = environ[index];

	free(environ);
	environ = current_environ;
	environ[index] = current_value;
	environ[index + 1] = NULL;

	return (0);
}



/**
 * shellby_unsetenv - This function deletes an environmental variable
 * from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: Double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to be removed
 *
 * Return: -1 if an error occurs, otherwise 0
 */

int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **current_environ;
	size_t size;
	int index, index2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	current_environ = malloc(sizeof(char *) * size);
	if (!current_environ)
		return (create_error(args, -1));

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env_var == environ[index])
		{
			free(*env_var);
			continue;
		}
		current_environ[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = current_environ;
	environ[size - 1] = NULL;

	return (0);
}
