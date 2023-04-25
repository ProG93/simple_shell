#include "shell.h"

/**
 * klint_r - function to replace string
 * @old: prev string
 * @new: new string
 *
 * Return: 1 or 0
 */
int klint_r(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
