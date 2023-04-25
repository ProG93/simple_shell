#include "main.h"

char *getline()
{
	char *str = NULL;
	size_t n;

	printf(">>> ");
	if (getline(&str, &n, stdin) == -1)
	{
		free(str);
		exit(0);
	}
	tokenizer(str);
}
