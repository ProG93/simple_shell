#include "main.h"

char **tokeniser(char *str)
{
	char *strcpy = NULL, *token = NULL;
	char **arg = NULL;
	int argc = 0, j = 0;
	struct stat st;

	strcpy = strdup(str);
	token = strtok(str, " \n");

	while (token)
		token = strtok(NULL, "\n"), argc++;
	arg = malloc(sizeog(char *) * argc);

	token = strtok(strcpy, " \n");
	while(token)
	arg[j++] = token, token = strtok(NULL, " \n");

	arg[j] = NULL;
	if (arg[0][0] == '/' && stat(str, &st) == 0)
		exec(arg);
	file_stat(arg[0], arg);
}
