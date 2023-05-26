#include "shell.h"

int _strlen(const char *l);
char *_strcpy(char *dest, const char *sc);
char *_strcat(char *dest, const char *sc);
char *_strncat(char *dest, const char *sc, size_t n);

/**
 * _strlen - To return the length of a string.
 * @s: A pointer to the characters string.
 *
 * Return: The length of the character.
 */
int _strlen(const char *l)
{
	int len = 0;

	if (!l)
		return (len);
	for (len = 0; l[len]; len++)
		;
	return (len);
}

/**
 * _strcpy - Copies the string pointed to sc 
 *           to the buffer pointed by des.
 * @dest: Pointer to the destination of copied string.
 * @sc: Pointer to the sc of the source string.
 *
 * Return: Pointer to dest.
 */
char *_strcpy(char *dest, const char *sc)
{
	size_t j;

	for (j = 0; sc[j] != '\0'; j++)
		dest[j] = sc[j];
	dest[j] = '\0';
	return (dest);
}

/**
 * _strcat - Concantenates two strings.
 * @dest: Pointer to destination string.
 * @sc: Pointer to source string.
 *
 * Return: Pointer to destination string.
 */
char *_strcat(char *dest, const char *sc)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp =  sc;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * _strncat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @sc: Pointer to source string.
 * @n: n bytes to copy from sc.
 *
 * Return: Pointer to destination string.
 */
char *_strncat(char *dest, const char *sc, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t j;

	for (j = 0; j < n && sc[j] != '\0'; j++)
		dest[dest_len + j] = sc[j];
	dest[dest_len + j] = '\0';

	return (dest);
}
