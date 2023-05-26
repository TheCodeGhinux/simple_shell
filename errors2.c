#include "shell.h"

char *err_126(char **args);
char *err_127(char **args);

/**
 * err_126 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *err_126(char **args)
{
	char *error, *h_str;
	int len;

	h_str = _itoa(hist);
	if (!h_str)
		return (NULL);

	len = _strlen(name) + _strlen(h_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(h_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, h_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(h_str);
	return (error);
}

/**
 * err_127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *err_127(char **args)
{
	char *error, *h_str;
	int len;

	h_str = _itoa(hist);
	if (!h_str)
		return (NULL);

	len = _strlen(name) + _strlen(h_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(h_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, h_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(h_str);
	return (error);
}
