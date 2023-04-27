#include "shell.h"

/**
 * free_bret - function to free bret_t struct field
 * @bret: passed struct
 * @all: 1 on freeing fiellds
 * Return: void
 */
void free_bret(bret_t *bret, int all)
{
	ffree(bret->argv);
	bret->argv = NULL;
	bret->path = NULL;
	if (all)
	{
		if (!bret->cmd_buf)
		{
			free(bret->arg);
		}
		if (bret->env)
		{
			free_list(&(bret->env));
		}
		if (bret->history)
		{
			free_list(&(bret->history));
		}
		if (bret->alias)
		{
			free_list(&(bret->alias));
		}
		ffree(bret->environ);
		bret->environ = NULL;
		klint_f((void **)bret->cmd_buf);
		if (bret->readfd > 2)
		{
			close(bret->readfd);
		}
		_putchar(BUF_FLUSH);
	}
}


/**
 * get_history_file - function to get history file
 * @bret: passed struct
 *
 * Return: allocated string
 */
char *get_history_file(bret_t *bret)
{
	char *buff, *dirr;

	dirr = _getenv(bret, "HOME=");
	if (!dirr)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dirr) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dirr);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}


/**
 * klint_v - function to create or append to an existing file
 * @bret: passed struct
 *
 * Return: 1 or -1
 */
int klint_v(bret_t *bret)
{
	ssize_t fdr;
	char *filenames = get_history_file(bret);
	list_t *node = NULL;

	if (!filenames)
		return (-1);

	fdr = open(filenames, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenames);
	if (fdr == -1)
		return (-1);
	for (node = bret->history; node; node = node->next)
	{
		_klint_e(node->str, fdr);
		_putfd('\n', fdr);
	}
	_putfd(BUF_FLUSH, fdr);
	close(fdr);
	return (1);
}


/**
 * klint_w - reads history from file
 * @bret: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int klint_w(bret_t *bret)
{
	int a, last = 0, count = 0;
	ssize_t fdr, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filenames = get_history_file(bret);

	if (!filenames)
		return (0);

	fdr = open(filenames, O_RDONLY);
	free(filenames);
	if (fdr == -1)
		return (0);
	if (!fstat(fdr, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fdr, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fdr);
	for (a = 0; a < fsize; a++)
		if (buf[a] == '\n')
		{
			buf[a] = 0;
			klint_x_list(bret, buf + last, count++);
			last = a + 1;
		}
	if (last != a)
		klint_x_list(bret, buf + last, count++);
	free(buf);
	bret->histcount = count;
	while (bret->histcount-- >= HIST_MAX)
		klint_t(&(bret->history), 0);
	renumber_history(bret);
	return (bret->histcount);
}


/**
 * klint_x_list - function to add entry to history
 * @bret: passed struct
 * @buf: passed buffer
 * @linecount: history linecount
 *
 * Return: 0
 */
int klint_x_list(bret_t *bret, char *buf, int linecount)
{
	list_t *node = NULL;

	if (bret->history)
		node = bret->history;
	add_node_end(&node, buf, linecount);

	if (!bret->history)
		bret->history = node;
	return (0);
}
