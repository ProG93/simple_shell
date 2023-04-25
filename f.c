#include "shell.h"

/**
 * _eputchar - function that writes the a char to stderr
 * @c: passed in char
 *
 * Return: 1 or -1
 */
int _eputchar(char c)
{
	static char b[WRITE_BUF_SIZE];
	static int a;

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, b, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		b[a++] = c;
	return (1);
}


/**
 * _putfd - function to write character to fd
 * @c: char to write
 * @fd: filedescriptor written to
 *
 * Return: 1 or -1
 */
int _putfd(char c, int fd)
{
	static int a;
	static char b[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, b, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		b[a++] = c;
	return (1);
}


/**
 * _klint_e - functiion to print input string
 * @str: string to print
 * @fd: filedescriptor
 *
 * Return: number of characters put into fd
 */
int _klint_e(char *str, int fd)
{
	int a = 0;

	if (!str)
		return (0);
	while (*str)
	{
		a += _putfd(*str++, fd);
	}
	return (a);
}


/**
 * _erratoi - function to convert string to integer
 * @s: string to convert
 * Return: 0 or -1
 */
int _erratoi(char *s)
{
	int a = 0;
	unsigned long int integer = 0;

	if (*s == '+')
		s++;
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			integer *= 10;
			integer += (s[a] - '0');
			if (integer > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (integer);
}


/**
 * print_error - function to print error message
 * @bret: passed struct
 * @estr: error type
 * Return: 0 or -1
 */
void print_error(bret_t *bret, char *estr)
{
	_kro(bret->fname);
	_kro(": ");
	print_d(bret->line_count, STDERR_FILENO);
	_kro(": ");
	_kro(bret->argv[0]);
	_kro(": ");
	_kro(estr);
}
