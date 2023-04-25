#include "shell.h"

/**
 **_strncat - function which concatenates two strings
 *@dest: first string
 *@src: second string
 *@n: the maximum amount of bytes to be used
 *Return: string
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *c = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
	{
		a++;
	}
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
	{
		dest[a] = '\0';
	}
	return (c);
}


/**
 **_strchr - function that locates a character in a string
 *@s: string
 *@c: character to identified
 *Return: pointer tocharacter
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
		{
			return (s);
		}
	} while (*s++ != '\0');

	return (NULL);
}


/**
 * input_buf - function for buffers chained commands
 * @bret: passed in struct
 * @buf: buffer
 * @len: len var
 *
 * Return: bytes that have be read
 */
ssize_t input_buf(bret_t *bret, char **buf, size_t *len)
{
	ssize_t a = 0;
	size_t b = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		#if USE_GETLINE
		a = getline(buf, &b, stdin);
		#else
		a = _getline(bret, buf, &b);
		#endif
		if (a > 0)
		{
			if ((*buf)[a - 1] == '\n')
			{
				(*buf)[a - 1] = '\0';
				a--;
			}
			bret->linecount_flag = 1;
			remove_comments(*buf);
			klint_x_list(bret, *buf, bret->histcount++);
			{
				*len = a;
				bret->cmd_buf = buf;
			}
		}
	}
	return (a);
}


/**
 * get_input - function that gets a line minus the newline
 * @bret: passed struct
 *
 * Return: bytes tat is read
 */
ssize_t get_input(bret_t *bret)
{
	static char *buf;
	static size_t a, b, c;
	ssize_t d = 0;
	char **e = &(bret->arg), *f;

	_putchar(BUF_FLUSH);
	d = input_buf(bret, &buf, &c);
	if (d == -1)
		return (-1);
	if (c)
	{
		b = a;
		f = buf + a;

		klint_p(bret, buf, &b, a, c);
		while (b < c)
		{
			if (is_chain(bret, buf, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= c)
		{
			a = c = 0;
			bret->cmd_buf_type = CMD_NORM;
		}

		*e = f;
		return (_strlen(f));
	}

	*e = buf;
	return (d);
}


/**
 * _myenv - function that prints the current directory
 * @bret: passed argument
 * Return: 0
 */
int _myenv(bret_t *bret)
{
	print_list_str(bret->env);
	return (0);
}
