/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:11 by hsano             #+#    #+#             */
/*   Updated: 2022/07/26 20:46:29 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	handling_end(char **p, char *old,  ssize_t read_num,ssize_t i)
{
	char	*lf;

	printf("tes handleind No.1\n");
	(*p)[i + BUFFER_SIZE] = '\0';
	lf = ft_memchr(&((*p)[i]), '\n', read_num);
	if (lf)
	{
		printf("tes handleind No.2\n");
		old = ft_strdup(lf + 1);
		lf[0] = '\0';
		return (true);
	}
	else if (read_num < 0 && errno != EINTR)
	{
		printf("tes handleind No.3\n");
		free(*p);
		old = NULL;
		return (true);
	}
	else if (read_num == 0)
	{
		printf("tes handleind No.5\n");
		free(*p);
		*p = NULL;
		old = NULL;
		return (true);
	}
	else if (read_num < BUFFER_SIZE)
	{
		printf("tes handleind No.4\n");
		lf = ft_memchr(&((*p)[i]), EOF, read_num);
		lf[0] = '\0';
		return (true);

	}
	printf("tes handleind No.6\n");
	return (false);
}

char	*mange_memory(char *old, size_t size)
{
	size_t	old_len;
	char	*p;

	old_len = ft_strlen(old);
	p = malloc(size + old_len + 1);
	if (!p)
	{
		if (old)
			free(old);
		return (NULL);
	}
	p = ft_strcpy(p, old);
	if (old)
		free(old);
	return (p);

}

char	*get_line(int fd, char *old, size_t size)
{
	size_t	i;
	char	*p;
	size_t	old_len;
	ssize_t	read_num;

	p = mange_memory(old, size);
	if (!p)
		return (NULL);
	old_len = ft_strlen(old);
	i = old_len;
	read_num = BUFFER_SIZE;
	while (read_num == BUFFER_SIZE)
	{
		read_num = read(fd, &(p[i]), BUFFER_SIZE);
		printf("get_line No.1 i=%zu, read_num=%zu/n",i,read_num);
		if (handling_end(&p, old, read_num, i))
			break;
		printf("get_line No.2 i=%zu/n",i);
		i += BUFFER_SIZE;
		printf("get_line No.3 i=%zu/n",i);
		if (i >= size + old_len + 1 - BUFFER_SIZE)
		{
			return (get_line(fd, p, size));
		}
		printf("get_line No.4 i=%zu/n",i);
	}
	printf("break\n");
	return (p);
}

char *get_next_line(int fd)
{
	size_t		size;
	char		*tmp;
	char		*swap;
	static char	*old;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	size = 0;
	if (BUFFER_SIZE > MIN_BUFFER_SIZE)
		size = BUFFER_SIZE;
	else
		size = MIN_BUFFER_SIZE;
	tmp = NULL;
	printf("test No.1\n");
	if (old != NULL && handling_end(&old, tmp, ft_strlen(old), 0))
	{
		printf("test No.2\n");
		swap = tmp;
		tmp = old;
		old = swap;
		return tmp;
	}
	printf("test No.3\n");
	return (get_line(fd, old, size));
}

