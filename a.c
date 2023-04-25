#include "shell.h"

/**
 * _klint_i - function that changes the current directory of process
 *
 * @bret: Struct containing arguments to maintain const funct prototype
 *
 * Return: 0
 */
int _klint_i(bret_t *bret)
{
	char *a, *b;
	char buffer[1024];
	int c;

	a = getcwd(buffer, 1024);
	if (!a)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!bret->argv[1])
	{
		b = _getenv(bret, "HOME=");
		if (!b)
			c = chdir((b = _getenv(bret, "PWD=")) ? b : "/");
		else
			c = chdir(b);
	}
	else if (_strcmp(bret->argv[1], "-") == 0)
	{
		if (!_getenv(bret, "OLDPWD="))
		{
			_puts(a);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(bret, "OLDPWD=")), _putchar('\n');
		c = chdir((b = _getenv(bret, "OLDPWD=")) ? b : "/");
	}
	else
		c = chdir(bret->argv[1]);
	if (c == -1)
	{
		print_error(bret, "can't cd to ");
		_kro(bret->argv[1]), _kor('\n');
	}
	else
	{
		_setenv(bret, "OLDPWD", _getenv(bret, "PWD="));
		_setenv(bret, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}


/**
 * _klint_j - function that changes current directory of process
 *
 * @bret: argument for struct containg argument used for const funct prototype
 *
 * Return: 0
 */
int _klint_j(bret_t *bret)
{
	char **arg_array;

	arg_array = bret->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
	{
		_puts(*arg_array);
	}
	return (0);
}


/**
 * _klint_k - function that displays history list, one cmd by line, preceded
 *            with line numbers, starting at 0.
 *
 * @bret: structure of potential arguments to maintain const funct prototype
 *
 *  Return: 0
 */
int _klint_k(bret_t *bret)
{
	print_list(bret->history);
	return (0);
}


/**
 * unset_alias - function to set alias to string
 *
 * @bret: argument for parameter struct
 * @str: string alias
 *
 * Return: 0 or 1
 */
int unset_alias(bret_t *bret, char *str)
{
	char *a, b;
	int c;

	a = _strchr(str, '=');
	if (!a)
	{
		return (1);
	}
	b = *a;
	*a = 0;
	c = klint_t(&(bret->alias),
	   get_node_index(bret->alias, node_starts_with(bret->alias, str, -1)));
	*a = b;
	return (c);
}


/**
 * klint - function that returns STDIN_FILENO
 *
 * @bret: struct address FROM PASSED ARGUMENT
 *
 * Return: int
 */
int klint(bret_t *bret)
{
	return (isatty(STDIN_FILENO) && bret->readfd <= 2);
}
