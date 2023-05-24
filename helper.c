#include "shell.h"

/**
 * get_pid - This is a function that obtains the current process ID.
 * Description: This opens the stat file, a space-delimited file containing
 * information about the current process.
 * PID is the first word in the file. The function reads the PID into
 * a buffer and replace the space at the end with a \0 byte.
 *
 * Return: NULL if it fails otherwise - the current process ID.
 */

char *get_pid(void)
{
	size_t k = 0;
	char *buffer;
	ssize_t stat_file;

	stat_file = open("/proc/self/stat", O_RDONLY);
	if (stat_file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(stat_file);
		return (NULL);
	}
	read(stat_file, buffer, 120);
	while (buffer[k] != ' ')
		k++;
	buffer[k] = '\0';

	close(stat_file);
	return (buffer);
}

/**
 * get_env_value - This is a function that gets the value corresponding
 * to an environmental variable.
 * @beginning: An environmental variable to search for.
 * @len: Length of the environmental variable to search for.
 *
 * Return: An empty string if variable is not found,
 * 0therwise - environmental variable value.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */

char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * variable_replacement - this is use to handle variable replacement.
 * @line: Double pointer containing the command and arguments.
 * @exe_ret: Pointer to the return value of the last executed command
 * Description: This replaces $$ with current PID, $? with the return value
 * of the last executed program, and envrionmental variables
 * preceded by $ and their corresponding value.
 */
void variable_replacement(char **line, int *exe_ret)
{
	int k, l = 0, len;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (k = 0; old_line[k]; k++)
	{
		if (old_line[k] == '$' && old_line[k + 1] &&
				old_line[k + 1] != ' ')
		{
			if (old_line[k + 1] == '$')
			{
				replacement = get_pid();
				l = k + 2;
			}
			else if (old_line[k + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				l = k + 2;
			}
			else if (old_line[k + 1])
			{
				/* extract the variable name to search for */
				for (l = k + 1; old_line[l] &&
						old_line[l] != '$' &&
						old_line[l] != ' '; l++)
					;
				len = l - (k + 1);
				replacement = get_env_value(&old_line[k + 1], len);
			}
			new_line = malloc(k + _strlen(replacement)
					  + _strlen(&old_line[l]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, k);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[l]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			k = -1;
		}
	}
}

/**
 * free_args - This function frees the memory taken by args.
 * @args: A null-terminated double pointer containing commands or arguments.
 * @front: Double pointer to the beginning of argument.
 */

void free_args(char **args, char **front)
{
	size_t k;

	for (k = 0; args[k] || args[k + 1]; k++)
		free(args[k]);

	free(front);
}
