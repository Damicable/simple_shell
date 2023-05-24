#include "shell.h"

int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int err);

/**
 * num_len - This is a function that counts the digit length of a number.
 * @num: The number to be counted.
 *
 * Return: The digit length.
 */

int num_len(int num)
{
	unsigned int digit;
	int len = 1;

	if (num < 0)
	{
		len++;
		digit = num * -1;
	}
	else
	{
		digit = num;
	}
	while (digit > 9)
	{
		len++;
		digit /= 10;
	}

	return (len);
}

/**
 * _itoa - This function converts an integer to a string.
 * @num: The integer that is to be converted
 *
 * Return: The already converted string.
 */

char *_itoa(int num)
{
	char *buffer;
	int len = num_len(num);
	unsigned int digit;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		digit = num * -1;
		buffer[0] = '-';
	}
	else
	{
		digit = num;
	}

	len--;
	do {
		buffer[len] = (digit % 10) + '0';
		digit /= 10;
		len--;
	} while (digit > 0);

	return (buffer);
}


/**
 * create_error - A function that writes a custom error message
 * to standard error.
 * @args: An array of arguments passed
 * @err: The error value.
 *
 * Return: The error computed
 */

int create_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = error_env(args);
		break;
	case 1:
		error = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error_2_syntax(args);
		else
			error = error_2_cd(args);
		break;
	case 126:
		error = error_126(args);
		break;
	case 127:
		error = error_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}
