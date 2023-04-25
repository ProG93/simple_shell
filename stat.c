#include "main.h"

void file_stat(char *str, char **arg)
{
	int j = 0;
	char *token = NULL, *key = "PATH", *path = NULL;
	char **cmd_cpy;
	struct stat st;

	while (cmd[j])
		j++;
	cmd_cpy = malloc(sizeof(char *) * j);
	for (j = 0; cmd[j]; i++)
		cmd_cpy[j] = strdup(cmd[j]);
	cmd_cpy[j] = NULL;

	j = 0;
	while (cmd_cpy[j])
	{
		token = strtok(cmd_cpy[j++], "=");
		if (strcmp(key, token) == 0)
			break;
	}
	token = strtok(NULL, "\0");
	token = strtok(token, ":");

	while (token)
	{
		path = malloc(sizeof(char) * (strlen(token) + strlen(str) + 1));
		strcat(path, token), strcat(path, "/"), strcat(path, str);
		if (stat(path, &st) == 0)
		{
			arg[0] = strdup(path);
			exec(arg);
		}
		token = strtok(NULL, ":");
	}
	perror("not available");
	_getline();
}

