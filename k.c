#include "shell.h"

/**
 * renumber_history - function to renumber history linked list
 * @bret: passed struct
 *
 * Return: int
 */
int renumber_history(bret_t *bret)
{
	list_t *node = bret->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (bret->histcount = a);
}


/**
 * add_node - function to add a node to start in list
 * @head: head node
 * @str: field of node
 * @num: node index
 *
 * Return: list size
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *news_head;

	if (!head)
		return (NULL);
	news_head = malloc(sizeof(list_t));
	if (!news_head)
		return (NULL);
	_memset((void *)news_head, 0, sizeof(list_t));
	news_head->num = num;
	if (str)
	{
		news_head->str = _strdup(str);
		if (!news_head->str)
		{
			free(news_head);
			return (NULL);
		}
	}
	news_head->next = *head;
	*head = news_head;
	return (news_head);
}


/**
 * add_node_end - function to add node to end of list
 * @head: head node
 * @str: str field
 * @num: node index
 *
 * Return: size of the list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
	{
		return (NULL);
	}

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
	{
		return (NULL);
	}
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
		{
			node = node->next;
		}
		node->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (new_node);
}


/**
 * print_list_str - function to print only the str element of a list_t
 * @h: first node
 *
 * Return: size of list_t
 */
size_t print_list_str(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}



/**
 * klint_t - function to delete node at a particlar index
 * @head: first node
 * @index: index of node to be deleted
 *
 * Return: 1 or 0
 */
int klint_t(list_t **head, unsigned int index)
{
	list_t *node;
	list_t *prev_node;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (a == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		a++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}
