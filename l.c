#include "shell.h"

/**
 * free_list - function to free all nodes list
 * @head_ptr: head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *exts_node, *heads;

	if (!head_ptr || !*head_ptr)
		return;
	heads = *head_ptr;
	node = heads;
	while (node)
	{
		exts_node = node->next;
		free(node->str);
		free(node);
		node = exts_node;
	}
	*head_ptr = NULL;
}



/**
 * klint_s - function to determine length of linked list
 * @h: first node
 *
 * Return: list size
 */
size_t klint_s(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}


/**
 * list_to_strings - function to return array of strings of list->str
 * @head: first node
 *
 * Return: string array
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t a = klint_s(head);
	size_t b;
	char **strss;
	char *str;

	if (!head || !a)
		return (NULL);
	strss = malloc(sizeof(char *) * (a + 1));
	if (!strss)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(strss[b]);
			free(strss);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strss[a] = str;
	}
	strss[a] = NULL;
	return (strss);
}


/**
 * print_list - function to print all elements of list_t
 * @h: first node
 *
 * Return: list size
 */
size_t print_list(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}


/**
 * node_starts_with - function to return node which starts prefix
 * @node: list head
 * @prefix: the string to match
 * @c: next character
 *
 * Return: list_t
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *pp = NULL;

	while (node)
	{
		pp = starts_with(node->str, prefix);
		if (pp && ((c == -1) || (*pp == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
