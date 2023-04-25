#include "shellp.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
 * main - Entry point
 * @args: argument
 * @status: process status
 * Description: Execute a command
 * Return: 0
 */
int main(char *args[], int status)
{
	pid_t = pid;

	pid = fork();

	/*failure to fork*/
	if (pid == -1)
	{
		fprintf(stderr, "Error to fork\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("Child process: PID=%d, PPID=%d\n", getpid(), getppid());
		args[] = {"ls", "-l", NULL};
		execvp(args[0], args;

		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Parent process: PID=%d, PPID=%d\n", getpid(), getppid());

		wait(&status);
	}
	return (0);
}
