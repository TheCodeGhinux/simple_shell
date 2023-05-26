#include "shell.h"

char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);

/**
 * get_loc - To locate a command in the PATH.
 * @command: The command to locate.
 *
 * Return: The full pathname, else Null
 */
char *get_loc(char *command)
{
	char **path, *tmp;
	list_t *dirs, *head;
	struct stat st;

	path = env_get("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		tmp = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
		if (!tmp)
			return (NULL);

		_strcpy(tmp, dirs->dir);
		_strcat(tmp, "/");
		_strcat(tmp, command);

		if (stat(tmp, &st) == 0)
		{
			free_list(head);
			return (tmp);
		}

		dirs = dirs->next;
		free(tmp);
	}

	free_list(head);

	return (NULL);
}

/**
 * fill_path_dir - To copy paths but also replaces leading/sandwiched/trailing
 *		   colons (:) with cd
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the cd
 */
char *fill_path_dir(char *path)
{
	int j, length = 0;
	char *path_copy, *pwd;

	pwd = *(env_get("PWD")) + 4;
	for (j = 0; path[j]; j++)
	{
		if (path[j] == ':')
		{
			if (path[j + 1] == ':' || j == 0 || path[j + 1] == '\0')
				length += _strlen(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (j = 0; path[j]; j++)
	{
		if (path[j] == ':')
		{
			if (j == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[j + 1] == ':' || path[j + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[j], 1);
		}
	}
	return (path_copy);
}

/**
 * get_path_dir - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
list_t *get_path_dir(char *path)
{
	int i;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = _strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (i = 0; dirs[i]; i++)
	{
		if (add_node_end(&head, dirs[i]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
