#include "shell.h"

alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

/**
 * add_alias_end - To Add a node to the end of a alias_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 *
 * Return: a pointer to the new node, if error - Null
 */
alias_t *add_alias_end(alias_t **head, char *name, char *value)
{
	alias_t *new_n = malloc(sizeof(alias_t));
	alias_t *last;

	if (!new_n)
		return (NULL);

	new_n->next = NULL;
	new_n->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_n->name)
	{
		free(new_n);
		return (NULL);
	}
	new_n->value = value;
	_strcpy(new_n->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_n;
	}
	else
		*head = new_n;

	return (new_n);
}

/**
 * add_node_end - To add a node to the end of a list_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @dir: The directory path for the new node to contain.
 *
 * Return: a pointer to the new node, if error - Null
 */
list_t *add_node_end(list_t **head, char *dir)
{
	list_t *new_n = malloc(sizeof(list_t));
	list_t *last;

	if (!new_n)
		return (NULL);

	new_n->dir = dir;
	new_n->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_n;
	}
	else
		*head = new_n;

	return (new_n);
}

/**
 * free_alias_list - Frees a alias_t linked list.
 * @head: THe head of the alias_t list.
 */
void free_alias_list(alias_t *head)
{
	alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}

/**
 * free_list - Frees a list_t linked list.
 * @head: The head of the list_t list.
 */
void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
