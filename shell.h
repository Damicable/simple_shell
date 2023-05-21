#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

#define END_OF_FILE -2
#define EXIT -3

/** Global environemnt **/

extern char **environ;


/**
 * struct list_s - This is a struct type defining a linked list.
 * @dir: Directory path.
 * @next: This is a pointer to another struct list_s.
 */

typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - This is a struct type defining builtin command
 * in this project
 * @name: Builtin command name.
 * @f: This is a function pointer to the builtin command's function.
 */

typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - This is a new struct defining aliases.
 * @name: The alias name
 * @value: The value of alias.
 * @next: A pointer to another struct alias_s.
 */

typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Global environemnt */

extern char **environ;

/** Global variables **/
int hist;
char *name;

/** String functions **/

char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strncmp(const char *s1, const char *s2, size_t n);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);

int cant_open(char *file_path)
int proc_file_commands(char *file_path, int *exe_ret);

/** Builtin Helpers **/

char **_getenv(const char *var);
char **_copyenv(void);
void free_env(void);

/** Main Builtins **/

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);


/** Main Helpers **/

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
char *get_location(char *command);
list_t *get_path_dir(char *path);
int execute(char **args, char **front);
void free_list(list_t *head);
char *_itoa(int num);
int num_len(int num);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);

int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);

/** Handled Error **/

int create_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_cd(char **args);
char *error_2_exit(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

#endif
