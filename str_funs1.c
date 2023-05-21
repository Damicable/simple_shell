#include "shell.h"

char *_strchr(char *s, char c);
int _strncmp(const char *s1, const char *s2, size_t n);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);

/**
 * _strchr - A function that locates a character in a string.
 * @s: The string in question.
 * @c: The character to be located.
 *
 * Return: A pointer to the first chr if c if located, otherwise NULL
 */

char *_strchr(char *s, char c)
{
	int index;

	for (index = 0; s[index]; index++)
	{
		if (s[index] == c)
			return (s + index);
	}

	return (NULL);
}

/**
 * _strncmp -A function that compare two strings.
 * @s1: A pointer to the first string.
 * @s2: A pointer to second string.
 * @n: The first n bytes of the two strings to compare.
 *
 * Return: <0 If s1 is shorter than s2.
 *         0 if s1 and s2 match.
 *        >0 if s1 is longer than s2.
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t k;

	for (k = 0; s1[k] && s2[k] && k < n; k++)
	{
		if (s1[k] > s2[k])
			return (s1[k] - s2[k]);
		else if (s1[k] < s2[k])
			return (s1[k] - s2[k]);
	}
	if (k == n)
		return (0);
	else
		return (-15);
}

/**
 * _strspn - A function that obtains the length of a prefix substring.
 * @s: The string to search through.
 * @accept: The prefix that the length is to be obained.
 *
 * Return: The n number of bytes from accept.
 */

int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int index;

	while (*s)
	{
		for (index = 0; accept[index]; index++)
		{
			if (*s == accept[index])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}

/**
 * _strcmp - A function that compares two strings.
 * @s1: The first string involved.
 * @s2: The second stringinvolved.
 *
 * Return: Positive byte difference if s1 > s2
 *         0 if s1 = s2
 *         Negative byte difference if s1 < s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}
