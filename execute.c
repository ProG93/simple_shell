#include "main.h"

void exec(char **arg)
{
	if (fork() == 0)
	{
		if (execve(arg[0], arg, cmd) == -1)
			perror("");
	}
	else
	{
		wait(NULL);
		_getline();
	}
}
