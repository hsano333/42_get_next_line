/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:11 by hsano             #+#    #+#             */
/*   Updated: 2022/07/26 02:52:00 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*mange_memory(char *old, size_t size)
{
	size_t	old_len;
	char	*p;

	old_len = ft_strlen(old);
	p = malloc(size + old_len + 1);
	if (!p)
		return (NULL);
	p = ft_strcpy(p, old);
	if (old)
		free(old);
	return (p);

}

char	*get_line(int fd, char *old, size_t size)
{
	size_t	i;
	char	*p;
	char	*lf;
	size_t	old_len;
	size_t	byte_num;

	p = mange_memory(old, size);
	old_len = ft_strlen(old);
	i = old_len;
	byte_num = BUFFER_SIZE;
	while (byte_num == BUFFER_SIZE  )
	{
		byte_num = read(fd, &(p[i]), BUFFER_SIZE);
		lf = ft_memchr(&(p[i]), '\n', BUFFER_SIZE);
		if (lf)
			return (p);
		if (byte_num < 0 && errno != EINTR)
			return (p);
		i += BUFFER_SIZE;
		if (i < size + old_len + 1 - BUFFER_SIZE)
		{
			p[i] = '\0';
			return (get_line(fd, p, size));
		}
	}
	return p;
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

	/*
	while (byte_num == BUFFER_SIZE)
	{
		p = get_p(fd, old);
		byte_num = read(fd, p, BUFFER_SIZE);
		if (byte_num < 0 && errno != EINTR)
			return (FALSE);
		p = p + SIZE;
	}
	*/
}
