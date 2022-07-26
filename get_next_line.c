/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:11 by hsano             #+#    #+#             */
/*   Updated: 2022/07/26 13:16:21 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	handling_end(char **p, char *old,  ssize_t read_num,ssize_t i)
{
	char	*lf;

	(*p)[i + BUFFER_SIZE] = '\0';
	lf = ft_memchr(&((*p)[i]), '\n', BUFFER_SIZE);
	if (read_num < 0 && errno != EINTR)
	{
		free(*p);
		old = NULL;
		return (true);
	}
	else if (read_num == 0)
	{
		free(*p);
		*p = NULL;
		//old = NULL;
		return (true);
	}
	else if (lf)
		return (true);
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
		if (handling_end(&p, old, read_num, i))
			break;
		i += BUFFER_SIZE;
		if (i >= size + old_len + 1 - BUFFER_SIZE)
		{
			return (get_line(fd, p, size));
		}
	}
	return (p);
}

char *get_next_line(int fd)
{
	size_t		size;
	static char	*old;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	size = 0;
	if (BUFFER_SIZE > MIN_BUFFER_SIZE)
		size = BUFFER_SIZE;
	else
		size = MIN_BUFFER_SIZE;
	return (get_line(fd, old, size));
}
