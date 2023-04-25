#include "shell.h"

/**
 * klint_g - function that checks if a character is a delimeter
 *
 * @c: the character to be checked
 * @delim: the delimeter string used for comparism
 * Return: 0 if false, 1 if true
 */
int klint_g(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
		{
			return (1);
		}
	}
	return (0);
}


/**
 * _isalpha - function that checks for alphabetic character
 * @c: character passed into function
 * Return: 1 if char is alphabetic and 0 otherwise if not
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}


/**
 * _atoi - function to convert string to integer
 * @s: the string passed in
 * Return: integer ,otherwise return 0
 */
int _atoi(char *s)
{
	int a, b, c, d;
	unsigned int e = 0;

	b = 1;
	c = 0;

	for (a = 0; s[a] != '\0' && c != 2; a++)
	{
		if (s[a] == '-')
			b *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			c = 1;
			e *= 10;
			e += (s[a] - '0');
		}
		else if (c == 1)
			c = 2;
	}

	if (b == -1)
		d = -e;
	else
		d = e;

	return (d);
}


/**
 * _klint_h - function to exit the shell
 * @bret: struct containing potential args
 * Return: exits
 */
int _klint_h(bret_t *bret)
{
	int ex;

	if (bret->argv[1])
	{
		ex = _erratoi(bret->argv[1]);
		if (ex == -1)
		{
			bret->status = 2;
			print_error(bret, "Illegal number: ");
			_kro(bret->argv[1]);
			_kor('\n');
			return (1);
		}
		bret->err_num = _erratoi(bret->argv[1]);
		return (-2);
	}
	bret->err_num = -1;
	return (-2);
}


/**
 * set_alias - function that sets alias to string
 * @bret: passed in struct
 * @str: passed in string alias
 *
 * Return: 0 or 1
 */
int set_alias(bret_t *bret, char *str)
{
	char *a;

	a = _strchr(str, '=');
	if (!a)
	{
		return (1);
	}
	if (!*++a)
	{
		return (unset_alias(bret, str));
	}

	unset_alias(bret, str);
	return (add_node_end(&(bret->alias), str, 0) == NULL);
}
