#include "shell.h"

/**
 * get_node_index - function to get index of node
 * @head: list head
 * @node: node
 *
 * Return: node index
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}


/**
 * klint_c - function to fork execution thread to run command
 * @bret: passed struct
 *
 * Return: void
 */
void klint_c(bret_t *bret)
{
	pid_t good;

	good = fork();
	if (good == -1)
	{
		perror("Error:");
		return;
	}
	if (good == 0)
	{
		if (execve(bret->path, bret->argv, get_environ(bret)) == -1)
		{
			free_bret(bret, 1);
			if (errno == EACCES)
			{
				exit(126);
			}
			exit(1);
		}
	}
	else
	{
		wait(&(bret->status));
		if (WIFEXITED(bret->status))
		{
			bret->status = WEXITSTATUS(bret->status);
			if (bret->status == 126)
			{
				print_error(bret, "Permission denied\n");
			}
		}
	}
}


/**
 * _strlen - function to return length of string
 * @s: passed string
 *
 * Return: string length
 */
int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;
	return (a);
}


/**
 * _strcmp - function to execute lexicogarphic comparison of two strings
 * @s1: first strang
 * @s2: second strang
 *
 * Return: -ve, 0 or +ve
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	if (*s1 == *s2)
	{
		return (0);
	}
	else
	{
		return (*s1 < *s2 ? -1 : 1);
	}
}


/**
 * klint_f - function to free pointer and NULLs address
 * @ptr: pointer to free
 *
 * Return: 1 or 0
 */
int klint_f(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
