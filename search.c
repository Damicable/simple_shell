#include "shell.h"

char *get_location(char *command);
list_t *get_path_dir(char *path);
char *fill_path_dir(char *path);

/**
 * get_location - This is a function that locates a command in the PATH.
 * @command: A command to locate.
 *
 * Return: NULL, if an error occur otherwise, the command full pathname
 */

char *get_location(char *command)
{
	char **path, *temp;
	list_t *dire, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dire = get_path_dir(*path + 5);
	head = dire;

	while (dire)
	{
		temp = malloc(_strlen(dire->dir) + _strlen(command) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, dire->dir);
		_strcat(temp, "/");
		_strcat(temp, command);

		if (stat(temp, &st) == 0)
		{
			free_list(head);
			return (temp);
		}

		dire = dire->next;
		free(temp);
	}

	free_list(head);

	return (NULL);
}

/**
 * get_path_dir - This is a function that tokenizes a colon-separated
 * list of directories into a list_s linked list.
 * @path: Colon-separated list of directories.
 *
 * Return: A pointer that points to the initialize linked list.
 */

list_t *get_path_dir(char *path)
{
	int index;
	char **dire, *path_copy;
	list_t *head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dire = _strtok(path_copy, ":");
	free(path_copy);
	if (!dire)
		return (NULL);

	for (index = 0; dire[index]; index++)
	{
		if (add_node_end(&head, dire[index]) == NULL)
		{
			free_list(head);
			free(dire);
			return (NULL);
		}
	}

	free(dire);

	return (head);
}

/**
 * fill_path_dir - This function, copies path and also replaces
 * leading/sandwiched/trailing colons (:) with the current
 * working directory.
 * @path: Colon-separated list of directories.
 *
 * Return: A copy of the path with any replaced leading/sandwiched/
 * trailing colons with the current working directory.
 */

char *fill_path_dir(char *path)
{
	int k, length = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (k = 0; path[k]; k++)
	{
		if (path[k] == ':')
		{
			if (path[k + 1] == ':' || k == 0 || path[k + 1] == '\0')
				length += _strlen(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (k = 0; path[k]; k++)
	{
		if (path[k] == ':')
		{
			if (k == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[k + 1] == ':' || path[k + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[k], 1);
		}
	}
	return (path_copy);
}
