#include "shell.h"

char **env_copy(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * env_copy - To create a copy of the environment.
 *
 * Return: a double pointer to the new copy.
 *          If error occurs - NULL.
 */
char **env_copy(void)
{
	char **new_env;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;

	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_env[index] = malloc(_strlen(environ[index]) + 1);

		if (!new_env[index])
		{
			for (index--; index >= 0; index--)
				free(new_env[index]);
			free(new_env);
			return (NULL);
		}
		_strcpy(new_env[index], environ[index]);
	}
	new_env[index] = NULL;

	return (new_env);
}

/**
 * free_env - Frees the the environment copy.
 */
void free_env(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * env_get - To get the environmental variable from PATH.
 * @var: Name of the environmental variable to get.
 *
 * Return: A pointer to the environmental variable.
 *         Else - Null
 */
char **env_get(const char *var)
{
	int index, len;

	len = _strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(var, environ[index], len) == 0)
			return (&environ[index]);
	}

	return (NULL);
}
