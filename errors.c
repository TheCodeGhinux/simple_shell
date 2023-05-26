#include "shell.h"

int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int err);

/**
 * num_len - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int num_len(int num)
{
	unsigned int i;
	int len = 1;

	if (num < 0)
	{
		len++;
		i = num * -1;
	}
	else
	{
		i = num;
	}
	while (i > 9)
	{
		len++;
		i /= 10;
	}

	return (len);
}

/**
 * _itoa - To convert an integer tostring.
 * @num: The integer.
 *
 * Return: Converted string.
 */
char *_itoa(int num)
{
	char *buffer;
	int len = num_len(num);
	unsigned int i;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		i = num * -1;
		buffer[0] = '-';
	}
	else
	{
		i = num;
	}

	len--;
	do {
		buffer[len] = (i % 10) + '0';
		i /= 10;
		len--;
	} while (i > 0);

	return (buffer);
}


/**
 * create_error - Writes a custom error message to stderr.
 * @args: Aaray of arguments.
 * @err: Error value.
 *
 * Return: The error value.
 */
int create_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = err_env(args);
		break;
	case 1:
		error = err_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = err_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = err_2_syntax(args);
		else
			error = err_2_cd(args);
		break;
	case 126:
		error = err_126(args);
		break;
	case 127:
		error = err_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}
