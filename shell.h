#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>

#define CONVERT_UNSIGNED 2
#define USE_GETLINE 0
#define READ_BUF_SIZE 1024
#define USE_STRTOK 0
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096
#define CMD_NORM 0
#define BUF_FLUSH -1
#define CMD_AND 2
#define CMD_OR 1
#define WRITE_BUF_SIZE 1024
#define CMD_CHAIN 3
#define CONVERT_LOWERCASE 1

extern char **environ;

/**
 * struct liststr - listr
 * @num: number integer
 * @str: character string
 * @next: pointer to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passbret - passbret
 * @status: status of executed command
 * @cmd_buf: pointer to command buffer
 * @cmd_buf_type: type of CMD
 * @readfd: fd from imput
 * @histcount: track line count
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: error on exit
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @env: copy of linked list
 * @environ: copy of env
 * @history: node computation
 * @alias: node for alias
 * @env_changed: track changes in environment
 * @linecount_flag: input line count
 * @fname: filename
 */
typedef struct passbret
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} bret_t;

#define BRET_INIT \
	{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	 0, 0, 0}

/**
 * struct builtin - builtin
 * @type: the command flag
 * @func: the function of the struct
 */
typedef struct builtin
{
	char *type;
	int (*func)(bret_t *);
} builtin_table;


int klint_a(bret_t *, char **);
int klint_built(bret_t *);
void klint_b(bret_t *);
void klint_c(bret_t *);
int klint_d(bret_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(bret_t *, char *, char *);
int loopklint_a(char **);
void _kro(char *);
int _kor(char);
int _putfd(char c, int fd);
int _klint_e(char *str, int fd);
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **strtow(char *, char *);
char **strtow2(char *, char);
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int klint_f(void **);
int klint(bret_t *);
int klint_g(char, char *);
int _isalpha(int);
int _atoi(char *);
int _erratoi(char *);
void print_error(bret_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _klint_h(bret_t *);
int _klint_i(bret_t *);
int _klint_j(bret_t *);
int _klint_k(bret_t *);
int _klint_l(bret_t *);
ssize_t get_input(bret_t *);
int _getline(bret_t *, char **, size_t *);
void sigintHandler(int);
void clear_bret(bret_t *);
void set_bret(bret_t *, char **);
void free_bret(bret_t *, int);
char *_getenv(bret_t *, const char *);
int _myenv(bret_t *);
int _klint_m(bret_t *);
int _klint_n(bret_t *);
int w_d(bret_t *);
char **get_environ(bret_t *);
int _unsetenv(bret_t *, char *);
int _setenv(bret_t *, char *, char *);
char *get_history_file(bret_t *bret);
int klint_v(bret_t *bret);
int klint_w(bret_t *bret);
int klint_x_list(bret_t *bret, char *buf, int linecount);
int renumber_history(bret_t *bret);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int klint_t(list_t **, unsigned int);
void free_list(list_t **);
size_t klint_s(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
int is_chain(bret_t *, char *, size_t *);
void klint_p(bret_t *, char *, size_t *, size_t, size_t);
int klint_o(bret_t *);
int klint_q(bret_t *);
int klint_r(char **, char *);
int set_alias(bret_t *bret, char *str);
int unset_alias(bret_t *bret, char *str);


#endif
