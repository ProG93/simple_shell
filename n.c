#include "shell.h"

/**
 * klint_d - function to determine if file is exec command
 * @bret: passed struct
 * @path: fie path
 *
 * Return: 1 or 0
 */
int klint_d(bret_t *bret, char *path)
{
	struct stat st;

	(void)bret;
	if (!path || stat(path, &st))
	{
		return (0);
	}

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}



/**
 * dup_chars - function of duplicate characters
 * @pathstr: string PATH
 * @start: first index
 * @stop: exit index
 *
 * Return: new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int a, b;

	a = 0;
	b = 0;

	for (b = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buff[b++] = pathstr[a];
	buff[b] = 0;
	return (buff);
}


/**
 * find_path - function to find command in the PATH string
 * @bret: passed struct
 * @pathstr: PATH string
 * @cmd: command ro find
 *
 * Return: char
 */
char *find_path(bret_t *bret, char *pathstr, char *cmd)
{
	int a = 0;
	int b = 0;
	char *c;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (klint_d(bret, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			c = dup_chars(pathstr, b, a);
			if (!*c)
				_strcat(c, cmd);
			else
			{
				_strcat(c, "/");
				_strcat(c, cmd);
			}
			if (klint_d(bret, c))
				return (c);
			if (!pathstr[a])
				break;
			b = a;
		}
		a++;
	}
	return (NULL);
}


/**
 * _memset - function to fill memory with const byte
 * @s: memory area
 * @b: byte to fill *s
 * @n: amount of byte
 * Return: pointer to memory area
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}


/**
 * ffree - function to free string
 * @pp: passed string
 * Return: void
 */
void ffree(char **pp)
{
	char **z;

	z = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(z);
}
