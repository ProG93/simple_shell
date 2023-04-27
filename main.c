#include "shell.h"

/**
 * main - main function
 * @ac: number of args
 * @av: argument array
 *
 * description: for shell
 *
 * Return: 0 or 1
 */
int main(int ac, char **av)
{
	bret_t bret[] = { BRET_INIT };
	int w = 2;

	asm ("mov %1, %0\n\t"
	     "add $3, %0"
	     : "=r" (w)
	     : "r" (w));

	if (ac == 2)
	{
		w = open(av[1], O_RDONLY);
		if (w == -1)
		{
			if (errno == EACCES)
			{
				exit(126);
			}
			if (errno == ENOENT)
			{
				_kro(av[0]);
				_kro(": 0: Can't open ");
				_kro(av[1]);
				_kor('\n');
				_kor(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		bret->readfd = w;
	}
	w_d(bret);
	klint_w(bret);
	klint_a(bret, av);
	return (EXIT_SUCCESS);
}
