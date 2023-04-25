#include "shell.h"

/**
 * get_environ - function to return string copy of env
 * @bret: passed struct
 * Return: 0
 */
char **get_environ(bret_t *bret)
{
	if (!bret->environ || bret->env_changed)
	{
		bret->environ = list_to_strings(bret->env);
		bret->env_changed = 0;
	}
	return (bret->environ);
}


/**
 * _unsetenv - function to remove an var from env
 * @bret: passed struct
 * @var: passed string
 * Return: 0
 */
int _unsetenv(bret_t *bret, char *var)
{
	list_t *node = bret->env;
	size_t a = 0;
	char *b;

	if (!node || !var)
		return (0);

	while (node)
	{
		b = starts_with(node->str, var);
		if (b && *b == '=')
		{
			bret->env_changed = klint_t(&(bret->env), a);
			a = 0;
			node = bret->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (bret->env_changed);
}


/**
 * _setenv - function to initialize new or modify existing env variable
 * @bret: passed struct
 * @var: variable property
 * @value: variable value
 * Return: 0
 */
int _setenv(bret_t *bret, char *var, char *value)
{
	char *b = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	b = malloc(_strlen(var) + _strlen(value) + 2);
	if (!b)
		return (1);
	_strcpy(b, var);
	_strcat(b, "=");
	_strcat(b, value);
	node = bret->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = b;
			bret->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(bret->env), b, 0);
	free(b);
	bret->env_changed = 1;
	return (0);
}


/**
 * clear_bret - function to clear bret_t
 * @bret: passed struct
 * Return: void
 */
void clear_bret(bret_t *bret)
{
	bret->arg = NULL;
	bret->argv = NULL;
	bret->path = NULL;
	bret->argc = 0;
}


/**
 * set_bret - function to initialize bret_t
 * @bret: passed struct
 * @av: vector of argument
 * Return: void
 */
void set_bret(bret_t *bret, char **av)
{
	int a = 0;

	bret->fname = av[0];
	if (bret->arg)
	{
		bret->argv = strtow(bret->arg, " \t");
		if (!bret->argv)
		{
			bret->argv = malloc(sizeof(char *) * 2);
			if (bret->argv)
			{
				bret->argv[0] = _strdup(bret->arg);
				bret->argv[1] = NULL;
			}
		}
		for (a = 0; bret->argv && bret->argv[a]; a++)
			;
		bret->argc = a;

		klint_o(bret);
		klint_q(bret);
	}
}
