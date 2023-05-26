#include "shell.h"

void free_args(char **args, char **cmdline);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void var_replacement(char **args, int *exe_ret);

/**
 * free_args - To free up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @cmdline: A double pointer to the beginning of args.
 */
void free_args(char **args, char **cmdline)
{
	size_t j;

	for (j = 0; args[j] || args[j + 1]; j++)
		free(args[j]);

	free(cmdline);
}

/**
 * get_pid - To get the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL if it fails.
 */
char *get_pid(void)
{
	size_t j = 0;
	char *buffer;
	ssize_t i;

	i = open("/proc/self/stat", O_RDONLY);
	if (i == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(i);
		return (NULL);
	}
	read(i, buffer, 120);
	while (buffer[j] != ' ')
		i++;
	buffer[i] = '\0';

	close(i);
	return (buffer);
}

/**
 * get_env_value - Gets the value corresponding to an environmental variable.
 * @beginning: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in VARIABLE=VALUE format.
 */
char *get_env_value(char *beginning, int len)
{
	char **var_add;
	char *replacement = NULL, *tmp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	*var_add = getenv(var);
	free(var);
	if (var_add)
	{
		tmp = *var_add;
		while (*tmp != '=')
			tmp++;
		tmp++;
		replacement = malloc(_strlen(tmp) + 1);
		if (replacement)
			_strcpy(replacement, tmp);
	}

	return (replacement);
}

/**
 * variable_replacement - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void variable_replacement(char **line, int *exe_ret)
{
	int i, y = 0, len;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (i = 0; old_line[i]; i++)
	{
		if (old_line[i] == '$' && old_line[i + 1] &&
				old_line[i + 1] != ' ')
		{
			if (old_line[i + 1] == '$')
			{
				replacement = get_pid();
				y = i + 2;
			}
			else if (old_line[i + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				y = i + 2;
			}
			else if (old_line[i + 1])
			{
				/* extract the variable name to search for */
				for (y = i + 1; old_line[y] &&
						old_line[y] != '$' &&
						old_line[y] != ' '; y++)
					;
				len = y - (i + 1);
				replacement = get_env_value(&old_line[i + 1], len);
			}
			new_line = malloc(i + _strlen(replacement)
					  + _strlen(&old_line[y]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, i);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[y]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			i = -1;
		}
	}
}
