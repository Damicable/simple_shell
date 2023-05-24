#include "shell.h"

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/**
 * help_env - This displays information about the shellby builtin
 * command 'env'.
 */

void help_env(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_setenv -  This displays information on the shellby builtin
 * command 'setenv'.
 */

void help_setenv(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_unsetenv - This program displays information on the shellby
 * builtin command 'unsetenv'.
 */

void help_unsetenv(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_history - This function displays the history list, one command by
 * line, preceded with line numbers; printf is not allowed.
 * use this prototype: void help_history(void);
 * Return: 0
 */

void help_history(void)
{
	int k = 0;
	history_t *current = NULL;
	
	current = get_history();
	while (current)
	{
		write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, _itoa(k), _strlen(_itoa(k)));
		write(STDOUT_FILENO, "  ", 2);
		write(STDOUT_FILENO, current->cmd, _strlen(current->cmd));
		write(STDOUT_FILENO, "\n", 1);
		current = current->next;
		k++;
	}
}
