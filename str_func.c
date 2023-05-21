#include "shell.h"

char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);

/**
 * _strcat - A function that concantenates two strings.
 * @dest: A pointer to destination string.
 * @src: A pointer to source string.
 *
 * Return: Pointer to destination string.
 */

char *_strcat(char *dest, const char *src)
{
	char *dest_temp;
	const char *src_temp;

	dest_temp = dest;
	src_temp =  src;

	while (*dest_temp != '\0')
		dest_temp++;

	while (*src_temp != '\0')
		*dest_temp++ = *src_temp++;
	*dest_temp = '\0';
	return (dest);
}

/**
 * _strncat - A function that concantenates two strings with n number
 * of bytes copied from source.
 * @dest: A pointer to destination string.
 * @src: A pointer to source string.
 * @n: Number of bytes to copy from source string.
 *
 * Return: Pointer to destination string, *dest
 */

char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t k;

	for (k = 0; k < n && src[k] != '\0'; k++)
		dest[dest_len + k] = src[k];
	dest[dest_len + k] = '\0';

	return (dest);
}

/**
 * _strlen - A function that returns the length of a string.
 * @s: A pointer to the char string.
 *
 * Return: The length of the char string.
 */

int _strlen(const char *s)
{
	int length = 0;

	if (!s)
		return (length);
	for (length = 0; s[length]; length++)
		;
	return (length);
}

/**
 * _strcpy - A function that copies the string src is pointed to
 * including the terminating null byte to the buffer dest pointed to.
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the source of the copied string.
 *
 * Return: Pointer to the destination of the string copied.
 */

char *_strcpy(char *dest, const char *src)
{
	size_t k;

	for (k = 0; src[k] != '\0'; k++)
		dest[k] = src[k];
	dest[k] = '\0';
	return (dest);
}
