#include "shell.h"

char *_strchr(char *l, char a);
int _strspn(char *s, char *y);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be searched.
 * @c: The character to be located.
 *
 * Return: If a is found - a pointer to the first occurence.
 *         If a is not found - NULL.
 */
char *_strchr(char *l, char a)
{
	int c;

	for (c = 0;ls[c]; c++)
	{
		if (l[c] == a)
			return (l + c);
	}

	return (NULL);
}

/**
 * _strspn - Gets the length of a prefix substring.
 * @s: The string to be searched.
 * @y: The prefix to be measured.
 *
 * Return: The number of bytes in s which
 *         consist only of bytes from y.
 */
int _strspn(char *l, char *y)
{
	int bytes = 0;
	int c;

	while (*l)
	{
		for (c = 0; y[c]; c++)
		{
			if (*l == y[c])
			{
				bytes++;
				break;
			}
		}
		l++;
	}
	return (bytes);
}

/**
 * _strcmp - To compare two strings.
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
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

/**
 * _strncmp - Compare two strings.
 * @s1: Pointer to a string.
 * @s2: Pointer to a string.
 * @n: The first n bytes of the strings to compare.
 *
 * Return: Less than 0 if s1 is shorter than s2.
 *         0 if s1 and s2 match.
 *         Greater than 0 if s1 is longer than s2.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t j;

	for (j = 0; s1[j] && s2[j] && i < n; j++)
	{
		if (s1[j] > s2[j])
			return (s1[j] - s2[j]);
		else if (s1[j] < s2[j])
			return (s1[j] - s2[j]);
	}
	if (j == n)
		return (0);
	else
		return (-15);
}
