#include "shell.h"
/**
 * _kor - writes the char to stdout
 * @c: character to print
 * Return: On success
 */

int _kor(char c)
{
	return(write(1, &c, 1));
}
