#include "shell.h"

/**
 * _realloc - funct to reallocate block of memory
 * @ptr: prev malloced mem
 * @old_size: byte of previous men
 * @new_size: byte of new mem
 *
 * Return: memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *z;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	z = malloc(new_size);
	if (!z)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		z[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (z);
}


/**
 * klint_a - funct to loop main shell
 * @bret: passed struct
 * @av: argument vector
 *
 * Return: 0, 1 or error code
 */
int klint_a(bret_t *bret, char **av)
{
	ssize_t a = 0;
	int b = 0;

	while (a != -1 && b != -2)
	{
		clear_bret(bret);
		if (klint(bret))
			_puts("$ ");
		_kor(BUF_FLUSH);
		a = get_input(bret);
		if (a != -1)
		{
			set_bret(bret, av);
			b = klint_built(bret);
			if (b == -1)
				klint_b(bret);
		}
		else if (klint(bret))
			_putchar('\n');
		free_bret(bret, 0);
	}
	klint_v(bret);
	free_bret(bret, 1);
	if (!klint(bret) && bret->status)
		exit(bret->status);
	if (b == -2)
	{
		if (bret->err_num == -1)
			exit(bret->status);
		exit(bret->err_num);
	}
	return (b);
}


/**
 * klint_built - function to find builtin cmd
 * @bret: passed struct
 *
 * Return: -1, 0, 1, 2
 */
int klint_built(bret_t *bret)
{
	int a, b = -1;
	builtin_table builtintbl[] = {
		{"exit", _klint_h},
		{"env", _myenv},
		{"help", _klint_j},
		{"history", _klint_k},
		{"setenv", _klint_m},
		{"unsetenv", _klint_n},
		{"cd", _klint_i},
		{"alias", _klint_l},
		{NULL, NULL}
	};

	for (a = 0; builtintbl[a].type; a++)
		if (_strcmp(bret->argv[0], builtintbl[a].type) == 0)
		{
			bret->line_count++;
			b = builtintbl[a].func(bret);
			break;
		}
	return (b);
}


/**
 * klint_b - function to finds a cmd in PATH
 * @bret: passed struct
 *
 * Return: void
 */
void klint_b(bret_t *bret)
{
	char *path = NULL;
	int a, b;

	bret->path = bret->argv[0];
	if (bret->linecount_flag == 1)
	{
		bret->line_count++;
		bret->linecount_flag = 0;
	}
	for (a = 0, b = 0; bret->arg[a]; a++)
	{
		if (!klint_g(bret->arg[a], " \t\n"))
		{
			b++;
		}
	}
	if (!b)
	{
		return;
	}

	path = find_path(bret, _getenv(bret, "PATH="), bret->argv[0]);
	if (path)
	{
		bret->path = path;
		klint_c(bret);
	}
	else
	{
		if ((klint(bret) || _getenv(bret, "PATH=")
		    || bret->argv[0][0] == '/') && klint_d(bret, bret->argv[0]))
		{
			klint_c(bret);
		}
		else if (*(bret->arg) != '\n')
		{
			bret->status = 127;
			print_error(bret, "not found\n");
		}
	}
}


/**
 * starts_with - function to check for char in string
 * @haystack: passed string
 * @needle: substring to find
 *
 * Return: address of next char or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
		{
			return (NULL);
		}
	}
	return ((char *)haystack);
}
