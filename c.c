#include "shell.h"

/**
 * print_alias - function that prints alias string
 * @node: node containing alias
 *
 * Return: 0 or 1
 */
int print_alias(list_t *node)
{
	char *a, *b;

	a = NULL;
	b = NULL;

	if (node)
	{
		b = _strchr(node->str, '=');
		for (a = node->str; a <= b; a++)
		{
			_putchar(*a);
		}
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}


/**
 * _klint_l - function that mimics the alias builtin
 * @bret: structure of passed arguments
 *  Return: 0
 */
int _klint_l(bret_t *bret)
{
	int a = 0;
	char *b = NULL;
	list_t *node = NULL;

	if (bret->argc == 1)
	{
		node = bret->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; bret->argv[a]; a++)
	{
		b = _strchr(bret->argv[a], '=');
		if (b)
		{
			set_alias(bret, bret->argv[a]);
		}
		else
		{
		print_alias(node_starts_with(bret->alias, bret->argv[a], '='));
		}
	}

	return (0);
}


/**
 * convert_number - function to convert number
 * @num: number passed in
 * @base: base to be converted with
 * @flags: flags
 *
 * Return: converted string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *a;
	static char buffer[50];
	char b = 0, *c;
	unsigned long d = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		d = -num;
		b = '-';

	}
	a = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	c = &buffer[49];
	*c = '\0';

	do {
		*--c = a[d % base];
		d /= base;
	} while (d != 0);

	if (b)
		*--c = b;
	return (c);
}


/**
 * remove_comments - function to replace first instance of '#' with '\0'
 * @buf: string to modify
 *
 * Return: 0
 */

void remove_comments(char *buf)
{
	int a = 0;

	for (; buf[a] != '\0'; a++)
	{
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
	}
}


/**
 **_strncpy - function that copies a string
 *@dest: the string to copy
 *@src: source string
 *@n: number of chars to copy
 *Return: copied string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *c = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (c);
}
