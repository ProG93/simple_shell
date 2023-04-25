#include "shell.h"

/**
 * _strdup - function to duplicate string
 * @str: passed string
 *
 * Return: duplicated string
 */
char *_strdup(const char *str)
{
	int len_str = 0;
	char *dup;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len_str++;
	dup = malloc(sizeof(char) * (len_str + 1));
	if (!dup)
		return (NULL);
	for (len_str++; len_str--;)
		dup[len_str] = *--str;
	return (dup);
}


/**
 * _puts - function to print input string
 * @str: passed string
 *
 * Return: void
 */
void _puts(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_putchar(str[a]);
		a++;
	}
}


/**
 * _putchar - function to write char to standard output
 * @c: passed char
 *
 * Return: 1 or -1
 */
int _putchar(char c)
{
	static int a;
	static char b[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, b, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		b[a++] = c;
	return (1);
}


/**
 * **strtow - function to split string into words
 * @str: passed string
 * @d: delimeter string
 * Return: string or NULL
 */
char **strtow(char *str, char *d)
{
	int a, b, c, m, n = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!klint_g(str[a], d) && (klint_g(str[a + 1], d) || !str[a + 1]))
			n++;

	if (n == 0)
		return (NULL);
	s = malloc((1 + n) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < n; b++)
	{
		while (klint_g(str[a], d))
			a++;
		c = 0;
		while (!klint_g(str[a + c], d) && str[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < c; m++)
			s[b][m] = str[a++];
		s[b][m] = 0;
	}
	s[b] = NULL;
	return (s);
}


/**
 * **strtow2 - function that splits string to words
 * @str: passed string
 * @d: delimeter
 * Return:string or NULL
 */
char **strtow2(char *str, char d)
{
	int a, b, c, m, n = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
		    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			n++;
	if (n == 0)
		return (NULL);
	s = malloc((1 + n) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < n; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		c = 0;
		while (str[a + c] != d && str[a + c] && str[a + c] != d)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < c; m++)
			s[b][m] = str[a++];
		s[b][m] = 0;
	}
	s[b] = NULL;
	return (s);
}
