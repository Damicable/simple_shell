#include "shell.h"

/**
 * _copyenv - A function that creates a copy of the environment.
 *
 * Return: NULL if an error occurs otherwise,
 * a double pointer to the new copy.
 */

char **_copyenv(void)
{
	char **new_copy;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;

	new_copy = malloc(sizeof(char *) * (size + 1));
	if (!new_copy)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_copy[index] = malloc(_strlen(environ[index]) + 1);

		if (!new_copy[index])
		{
			for (index--; index >= 0; index--)
				free(new_copy[index]);
			free(new_copy);
			return (NULL);
		}
		_strcpy(new_copy[index], environ[index]);
	}
	new_copy[index] = NULL;

	return (new_copy);
}

/**
 * _getenv - This function gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return:  NULL if the environmental variable does not exist
 * otherwise, a pointer to the environmental variable.
 */

char **_getenv(const char *var)
{
	int index, len;

	len = _strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(var, environ[index], len) == 0)
			return (&environ[index]);
	}

	return (NULL);
}

/**
 * free_env - A function that frees the environment copy.
 */

void free_env(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}
