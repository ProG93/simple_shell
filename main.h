#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **cmd

char *_getline();
char **tokenizer(char *str);
void exec(char **arg);
void file_stat(char *str, char **arg);

#endif 
