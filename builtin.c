#include "shell.h"
int (*get_builtin(char *command))(char **args, char **cmdline);
int shell_exit(char **args, char **cmdline);
int shell_cd(char **args, char __attribute__((__unused__)) **cmdline);
int shell_help(char **args, char __attribute__((__unused__)) **cmdline);

/**
 * get_builtin - Match command with corresponding
 *               builtin shell function.
 * @command: The command to match.
 *
 * Return: Function pointers to corresponding builtin.
 */
int (*get_builtin(char *command))(char **args, char **cmdline)
{
	builtin_t funcs[] = {
		{ "exit", shell_exit },
		{ "env", shell_env },
		{ "setenv", shell_setenv },
		{ "unsetenv", shell_unsetenv },
		{ "cd", shell_cd },
		{ "alias", shell_alias },
		{ "help", shell_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * shell_help - To display information about shell builtin commands.
 * @args: An array of arguments.
 * @cmdline: A pointer to the beginning of args.
 *
 * Return: -1 If error occurs.
 *         Otherwise - 0.
 */
int shell_help(char **args, char __attribute__((__unused__)) **cmdline)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}

/**
 * shell_exit - Causes normal process termination
 *                for the shell shell.
 * @args: An array of arguments containing the exit value.
 * @cmdline: A double pointer to the beginning of args.
 *
 * Return: -3 If there are no arguments.
 *         -2 If the given exit value is invalid.
 *         O/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */
int shell_exit(char **args, char **cmdline)
{
	int i, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_args(args, cmdline);
	free_env();
	free_alias_list(aliases);
	exit(num);
}

/**
 * shell_cd - To change the current directory of the shell process.
 * @args: Array of arguments.
 * @cmdline: A double pointer to the beginning of args.
 *
 * Return: -2 If inputted string is not a directory.
 *         -1 If an error occurs.
 *         else  0.
 */
int shell_cd(char **args, char __attribute__((__unused__)) **cmdline)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(_getenv("HOME") + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (shell_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shell_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}
