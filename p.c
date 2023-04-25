#include "shell.h"

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}



/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}



/**
 * klint_p - checks we should continue chaining based on last status
 * @bret: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void klint_p(bret_t *bret, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (bret->cmd_buf_type == CMD_AND)
	{
		if (bret->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (bret->cmd_buf_type == CMD_OR)
	{
		if (!bret->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}




/**
 * klint_o - replaces an aliases in the tokenized string
 * @bret: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int klint_o(bret_t *bret)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(bret->alias, bret->argv[0], '=');
		if (!node)
			return (0);
		free(bret->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		bret->argv[0] = p;
	}
	return (1);
}




/**
 * klint_q - function to replace vars in token string
 * @bret: passed struct
 *
 * Return: 1 or 0
 */
int klint_q(bret_t *bret)
{
	int a = 0;
	list_t *node;

	for (a = 0; bret->argv[a]; a++)
	{
		if (bret->argv[a][0] != '$' || !bret->argv[a][1])
		{
			continue;
		}

		if (!_strcmp(bret->argv[a], "$?"))
		{
			klint_r(&(bret->argv[a]),
				_strdup(convert_number(bret->status, 10, 0)));
			continue;
		}
		if (!_strcmp(bret->argv[a], "$$"))
		{
			klint_r(&(bret->argv[a]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(bret->env, &bret->argv[a][1], '=');
		if (node)
		{
			klint_r(&(bret->argv[a]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		klint_r(&bret->argv[a], _strdup(""));

	}
	return (0);
}
