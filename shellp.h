#ifndef _SHELLP_H
#define _SHELLP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


void _getline(char *string, int size);
int _putchar(char c);
void alloc_int(int **grid, int height);
int main(char *args[], int status);

#endif 
