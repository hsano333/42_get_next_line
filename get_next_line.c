/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:11 by hsano             #+#    #+#             */
/*   Updated: 2022/07/28 12:47:02 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	exist_lf(char **p, char **old, ssize_t i)
{
	char	*lf;

	lf = ft_strnchr(*p, '\n', i);
	if (lf)
	{
		if (lf[1] != '\0')
			*old = ft_strdup(lf + 1);
		else
			*old = NULL;
		lf[1] = '\0';
		return (true);
	}
	return (false);
}

int	check_eof(char **p, char **old, ssize_t read_num, ssize_t i)
{
	if (read_num < 0)
	{
		if (errno == EINTR)
			return (false);
		free(*p);
		*p = NULL;
		return (true);
	}
	else if (read_num < BUFFER_SIZE)
	{
		if (i == 0)
		{
			free(*p);
			*p = NULL;
		}
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

char	*get_line(int fd, char **old, ssize_t size)
{
	char	*p;
	ssize_t	old_len;
	ssize_t	read_num;
	ssize_t	i;

	old_len = ft_strlen(*old);
	p = mange_memory(*old, size);
	if (!p)
		return (NULL);
	read_num = BUFFER_SIZE;
	i = old_len;
	while (read_num == BUFFER_SIZE)
	{
		read_num = read(fd, &(p[i]), BUFFER_SIZE);
		if (read_num > 0)
			i += read_num;
		p[i] = '\0';
		if (exist_lf(&p, old, i) || check_eof(&p, old, read_num, i))
			break ;
		if (i >= size + old_len - BUFFER_SIZE)
			return (get_line(fd, &p, size));
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
	if (old != NULL && (exist_lf(&old, &tmp, -1)))
	{
		if (old[0] == '\0')
			return (NULL);
		swap = tmp;
		tmp = old;
		old = swap;
		return (tmp);
	}
	return (get_line(fd, &old, size));
}
