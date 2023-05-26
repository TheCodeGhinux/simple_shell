#include "shell.h"

void line_ptr(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void chechk_logical_ops(char *line, ssize_t *new_len);

/**
 * line_ptr - Partitions a line read from standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @read: The length of line.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void line_ptr(char **line, ssize_t read)
{
	char *prev_line, *updated_line;
	char previous, current, next;
	size_t i, j;
	ssize_t new_len;

	new_len = get_new_len(*line);
	if (new_len == read - 1)
		return;
	updated_line = malloc(new_len + 1);
	if (!updated_line)
		return;
	j = 0;
	prev_line = *line;
	for (i = 0; prev_line[i]; i++)
	{
		current = prev_line[i];
		next = prev_line[i + 1];
		if (i != 0)
		{
			previous = prev_line[i - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					updated_line[j++] = ' ';
					updated_line[j++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					updated_line[j++] = ';';
					updated_line[j++] = ' ';
					continue;
				}
				if (previous != ' ')
					updated_line[j++] = ' ';
				updated_line[j++] = ';';
				if (next != ' ')
					updated_line[j++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					updated_line[j++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					updated_line[j++] = '&';
					updated_line[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					updated_line[j++]  = ' ';
				else if (previous == '|' && next != ' ')
				{
					updated_line[j++] = '|';
					updated_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (i != 0 && prev_line[i - 1] != ' ')
				updated_line[j++] = ' ';
			updated_line[j++] = ';';
			if (next != ' ' && next != ';')
				updated_line[j++] = ' ';
			continue;
		}
		updated_line[j++] = prev_line[i];
	}
	updated_line[j] = '\0';

	free(*line);
	*line = updated_line;
}

/**
 * get_new_len - To get the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 */

ssize_t get_new_len(char *line)
{
	size_t y;
	ssize_t new_len = 0;
	char current, next;

	for (y = 0; line[y]; y++)
	{
		current = line[y];
		next = line[y + 1];
		if (current == '#')
		{
			if (y == 0 || line[y - 1] == ' ')
			{
				line[y] = '\0';
				break;
			}
		}
		else if (y != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[y - 1] != ' ' && line[y - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[y - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[y - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				chechk_logical_ops(&line[y], &new_len);
		}
		else if (current == ';')
		{
			if (y != 0 && line[y - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}
/**
 * chechk_logical_ops - To check a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */
void chechk_logical_ops(char *line, ssize_t *new_len)
{
	char previous, current, next;

	previous = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*new_len)++;
		else if (previous == '&' && next != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*new_len)++;
		else if (previous == '|' && next != ' ')
			(*new_len)++;
	}
}
