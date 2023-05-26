#include "shell.h"

int token_len(char *str, char *delim);
int token_count(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len - Locates the delimiter index marking the end
 *             of the first token contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The delimiter i marking the end of
 *         the intitial token pointed to be str.
 */
int token_len(char *str, char *delim)
{
	int i = 0, len = 0;

	while (*(str + i) && *(str + i) != *delim)
	{
		len++;
		i++;
	}

	return (len);
}

/**
 * token_count - To count the number of delim words in a string.
 * @str: String to be searched.
 * @delim: Delimiter character.
 *
 * Return: Number of words contained in str.
 */
int token_count(char *str, char *delim)
{
	int i, tokens = 0, len = 0;

	for (i = 0; *(str + i); i++)
		len++;

	for (i = 0; i < len; i++)
	{
		if (*(str + i) != *delim)
		{
			tokens++;
			i += token_len(str + i, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - To tokenize a string.
 * @line: The string.
 * @delim: The delimiter character to tokenize the string by.
 *
 * Return: Pointer to array containing the tokenized words.
 */
char **_strtok(char *line, char *delim)
{
	char **j;
	int i = 0, tokens, t, letters, l;

	tokens = token_count(line, delim);
	if (tokens == 0)
		return (NULL);

	j = malloc(sizeof(char *) * (tokens + 2));
	if (!j)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[i] == *delim)
			i++;

		letters = token_len(line + i, delim);

		j[t] = malloc(sizeof(char) * (letters + 1));
		if (!j[t])
		{
			for (i -= 1; i >= 0; i--)
				free(j[i]);
			free(j);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			j[t][l] = line[i];
			i++;
		}

		j[t][l] = '\0';
	}
	j[t] = NULL;
	j[t + 1] = NULL;

	return (j);
}
