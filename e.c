#include "shell.h"

/**
 * _getenv - function that gets the value of an env variable
 * @bret: passed struct
 * @name: variable name
 *
 * Return: value of variable
 */
char *_getenv(bret_t *bret, const char *name)
{
	list_t *node = bret->env;
	char *x;

	while (node)
	{
		x = starts_with(node->str, name);
		if (x && *x)
			return (x);
		node = node->next;
	}
	return (NULL);
}


/**
 * _klint_m - function to initialize new env of modify existing one
 * @bret: passed structure
 * Return: 0
 */
int _klint_m(bret_t *bret)
{
	if (bret->argc != 3)
	{
		_kro("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(bret, bret->argv[1], bret->argv[2]))
	{
		return (0);
	}
	return (1);
}


/**
 * _klint_n - function that removes variable
 * @bret: passed structure
 * Return: 0
 */
int _klint_n(bret_t *bret)
{
	int a;

	if (bret->argc == 1)
	{
		_kro("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= bret->argc; a++)
		_unsetenv(bret, bret->argv[a]);

	return (0);
}


/**
 * populate_env_list - function that populates linked list
 * @bret: passed structure
 * Return: 0
 */
int populate_env_list(bret_t *bret)
{
	list_t *b = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&b, environ[a], 0);
	bret->env = b;
	return (0);
}


/**
 * _kro - functio that prints input string
 * @str: string to print
 *
 * Return: void
 */
void _kro(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_kor(str[a]);
		a++;
	}
}
