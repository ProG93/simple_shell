#include "shell.h"

/**
 * is_chain - function to test if current char is chain delimeter from buff
 * @bret: passed struct
 * @buf: character buff
 * @p: current position in buff
 *
 * Return: 1 or 0
 */
int is_chain(bret_t *bret, char *buf, size_t *p)
{
	size_t a = *p;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
		buf[a] = 0;
		a++;
		bret->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == '&' && buf[a + 1] == '&')
	{
		buf[a] = 0;
		a++;
		bret->cmd_buf_type = CMD_AND;
	}
	else if (buf[a] == ';')
	{
		buf[a] = 0;
		bret->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = a;
	return (1);
}


/**
 * print_d - function to print decimal number
 * @input: passed data
 * @fd: filedescriptor
 *
 * Return: number count
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a, num = 0;
	unsigned int _abs_, b;

	if (fd == STDERR_FILENO)
		__putchar = _kor;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		num++;
	}
	else
		_abs_ = input;
	b = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + b / a);
			num++;
		}
		b %= a;
	}
	__putchar('0' + b);
	num++;

	return (num);
}


/**
 * read_buf - function to read buff
 * @bret: passed struct
 * @buf: imput buffer
 * @i: size of buffer
 *
 * Return: read buffer (a)
 */
ssize_t read_buf(bret_t *bret, char *buf, size_t *i)
{
	ssize_t a = 0;

	if (*i)
		return (0);
	a = read(bret->readfd, buf, READ_BUF_SIZE);
	if (a >= 0)
		*i = a;
	return (a);
}


/**
 * _getline - function to imput next line of input from STANDARD IMPUT
 * @bret: passed struct
 * @ptr: passed buffer
 * @length: size of buffer
 *
 * Return: seed
 */
int _getline(bret_t *bret, char **ptr, size_t *length)
{
	static char z[READ_BUF_SIZE];
	static size_t a, len;
	size_t b;
	ssize_t reed = 0, seed = 0;
	char *x = NULL, *new_p = NULL, *y;

	x = *ptr;
	if (x && length)
		seed = *length;
	if (a == len)
		a = len = 0;

	reed = read_buf(bret, z, &len);
	if (reed == -1 || (reed == 0 && len == 0))
		return (-1);

	y = _strchr(z + a, '\n');
	b = y ? 1 + (unsigned int)(y - z) : len;
	new_p = _realloc(x, seed, seed ? seed + b : b + 1);
	if (!new_p)
		return (x ? free(x), -1 : -1);
	if (seed)
		_strncat(new_p, z + a, b - a);
	else
		_strncpy(new_p, z + a, b - a + 1);
	seed += b - a;
	a = b;
	x = new_p;

	if (length)
		*length = seed;
	*ptr = x;
	return (seed);
}


/**
 * sigintHandler - function to block ctrl-C
 * @sig_num: imput
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
