/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:11 by hsano             #+#    #+#             */
/*   Updated: 2022/07/27 21:02:46 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	parse_line(char **p, char **old, ssize_t read_num, ssize_t i)
{
	char	*lf;

	lf = ft_memchr(*p, '\n', read_num);
	if (lf)
	{
		if (lf[1] != '\0')
			*old = ft_strdup(lf + 1);
		else
			*old = NULL;
		lf[1] = '\0';
		return (true);
	}
	else if (read_num < BUFFER_SIZE && i != -1)
	{
		if ((read_num < 0 && errno != EINTR) || i == 0)
			free(*p);
		else
			(*p)[i] = '\0';
		*old = NULL;
		return (true);
	}
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

char	*get_line(int fd, char **old, size_t size, size_t i)
{
	char	*p;
	size_t	old_len;
	ssize_t	read_num;

	p = mange_memory(*old, size);
	if (!p)
		return (NULL);
	old_len = ft_strlen(*old);
	read_num = BUFFER_SIZE;
	while (read_num == BUFFER_SIZE)
	{
		read_num = read(fd, &(p[i]), BUFFER_SIZE);
		if (read_num > 0)
			i += read_num;
		if (parse_line(&p, old, read_num, i))
			break ;
		if (i >= size + old_len - BUFFER_SIZE)
		{
			p[i] = '\0';
			return (get_line(fd, &p, size, i));
		}
	}
	return (p);
}

char	*get_next_line(int fd)
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
	if (old != NULL && parse_line(&old, &tmp, ft_strlen(old), -1))
	{
		swap = tmp;
		tmp = old;
		old = swap;
		return (tmp);
	}
	return (get_line(fd, &old, size, 0));
}
