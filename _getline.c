#include "shellp.h"

/**
 * _getline -
 *@String: pointer to a string
 *@size: size of integer
 *Return: 0
 */

void _getline(char *string, int size)
{
	printf(">>> ");
	string = malloc(sizeof char*);
	if (getline(&string, &size, stdin) == -1)
	{
		_putchar("ERROR");
	}
	else
	{
		_putchar(string);
		_putchar("\n");
	}
	return (0);
}
