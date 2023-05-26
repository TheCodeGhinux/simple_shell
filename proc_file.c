#include "shell.h"

int cant_open(char *file_path);
int proc_comm(char *file_path, int *exe_ret);

/**
 * cant_open - It prints a cant open error
 *             If the file doesn't exist or no proper permissions.
 * @file_path: Path to the file.
 *
 * Return: 127.
 */

int cant_open(char *file_path)
{
	char *error, *h_str;
	int len;

	h_str = _itoa(hist);
	if (!h_str)
		return (127);

	len = _strlen(name) + _strlen(h_str) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(h_str);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, h_str);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(h_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * proc_comm - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int proc_comm(char *file_path, int *exe_ret)
{
	ssize_t file, read_b, i;
	unsigned int line_sz = 0;
	unsigned int old_sz = 120;
	char *line, **args, **cmdline;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_sz);
	if (!line)
		return (-1);
	do {
		read_b = read(file, buffer, 119);
		if (read_b == 0 && line_sz == 0)
			return (*exe_ret);
		buffer[read_b] = '\0';
		line_sz += read_b;
		line = re_alloc(line, old_sz, line_sz);
		_strcat(line, buffer);
		old_sz = line_sz;
	} while (read_b);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_sz; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_sz && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	variable_replacement(&line, exe_ret);
	line_ptr(&line, line_sz);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	cmdline = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = call_args(args, cmdline, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}

	ret = call_args(args, cmdline, exe_ret);

	free(cmdline);
	return (ret);
}
