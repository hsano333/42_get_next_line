/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:11 by hsano             #+#    #+#             */
/*   Updated: 2022/07/27 03:27:45 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	parse_line(char **p, char **old,  ssize_t read_num,ssize_t i)
{
	char	*lf;

	//(*p)[i + read_num] = '\0';
	lf = ft_memchr(*p, '\n', read_num);
	//printf("i=%zu,read_num=%zu, p=%s,lf=%s\n",i,read_num, *p,lf);
	if (lf)
	{
		printf("test No.1\n");
		*old = ft_strdup(lf + 1);
		lf[1] = '\0';
		//printf("old=%s, lf=%s,\n",*old,lf);
		//printf("old=%s,p=%s\n",*old,*p);
		return (true);
	}
	else if (read_num < 0 && errno != EINTR)
	{
		//printf("test No.2\n");
		free(*p);
		*old = NULL;
		return (true);
	}
	else if (read_num < BUFFER_SIZE)
	{
		/*
		lf = ft_memchr(*p, EOF, read_num);
		if (lf != NULL)
			lf[1] = '\0';
			*/
		printf("test No.3 i=%zu,lf=%s\n",i,lf);
		if (i == 0)
		{
			//printf("test No.4\n");
			//printf("");
			free(*p);
			*p = NULL;
		}
		//*p = NULL;
		*old = NULL;
		return (true);
	}
	else if (read_num < BUFFER_SIZE)
	{
		*p[i] = '\0';
		printf("test No.4\n");
		return (true);
	}
	printf("test No.5\n");
	return (false);
}

char	*mange_memory(char *old, size_t size)
{
	size_t	old_len;
	char	*p;

	old_len = ft_strlen(old);
	p = malloc(size + old_len + 1);
	p[size + old_len + 1] = '\0';
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

char	*get_line(int fd, char **old, size_t size)
{
	size_t	i;
	char	*p;
	size_t	old_len;
	ssize_t	read_num;

	p = mange_memory(*old, size);
	if (!p)
		return (NULL);
	old_len = ft_strlen(*old);
	i = old_len;
	read_num = BUFFER_SIZE;
	while (read_num == BUFFER_SIZE)
	{
		read_num = read(fd, &(p[i]), BUFFER_SIZE);
		//printf("read p=%s,i=%zu\n",p,i);
		if (parse_line(&p, old, read_num, i))
			break;
		i += read_num;
		if (i >= size + old_len + 1 - BUFFER_SIZE)
		{
			p[i] = '\0';
			return (get_line(fd, &p, size));
		}
	}
	//printf("p=%s\n",p);
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
	/*
	if (old != NULL)
		printf("old is not NULL\n");
	else
		printf("old is NULL\n");
		*/
	if (old != NULL && parse_line(&old, &tmp, ft_strlen(old), ft_strlen(old)))
	{
		swap = tmp;
		tmp = old;
		old = swap;
		return tmp;
	}
	return (get_line(fd, &old, size));
}

