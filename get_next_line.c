/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:11 by hsano             #+#    #+#             */
/*   Updated: 2022/07/28 03:37:48 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


int exist_lf(char **p, char **old, ssize_t i)
{
	char	*lf;

	//printf("exist lf No.1, i=%zu\n",i);
	lf = ft_strnchr(*p, '\n', i);
	if (lf)
	{
		//printf("exist lf No.2 p=%s\n",*p);
		if (lf[1] != '\0')
		{
			//printf("exist lf No.3 lf=%s:endlf\n",lf);
			*old = ft_strdup(lf + 1);
		}
		else
		{
			//printf("exist lf No.4\n");
			*old = NULL;
		}
		//printf("exist lf No.5 p=%s:pend, old=%s:oldend,\n",*p,*old);
		lf[1] = '\0';
		//printf("exist lf No.6 p=%s:pend, old=%s:oldend,\n",*p,*old);
		return (true);
	}
	//printf("exist lf No.7\n");
	return (false);
}

int check_eof(char **p, char **old, ssize_t read_num, ssize_t i)
{
	////printf("check eof No.1\n");
	if (read_num < 0)
	{
		//printf("check eof No.2\n");
		if (errno == EINTR)
			return (false);

		//printf("check eof No.3\n");
		free(*p);
		*p = NULL;
		return (true);
	}
	else if (read_num < BUFFER_SIZE)
	{
		//printf("check eof No.4\n");
		if (i == 0)
		{
			//printf("check eof No.5\n");
			free(*p);
			*p = NULL;
		}
		//else
			//*p = *old;
		//printf("check eof No.6 p=%s\n",*p);
		*old = NULL;
		return (true);
	}
		//printf("check eof No.7\n");
	/*
	if (read_num < BUFFER_SIZE && i != -1)
	{
		//else
		//{
			//(*p)[i] = '\0';
		//}
		*old = NULL;
		return (true);
	}
	*/
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

	old_len = ft_strlen(*old);
	//printf("get_line No.1 old_len=%zu,i=%zu\n",old_len,i);
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
		if (read_num < BUFFER_SIZE)
		{
			//printf("read_num less No.1 i=%zu, read_num=%zu\n",i,read_num);
			//p[i] = '\0';
			//p[i + 1] = 255;
		}
		if (exist_lf(&p, old, i) || check_eof(&p, old, read_num, i))
			break ;
		if (i >= size + old_len - BUFFER_SIZE)
		{
			//printf("fusoku memory i=%zu,p=%s\n",i,p);
			//p[i] = '\0';
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
	//printf("No.1\n");
	if (old != NULL && (exist_lf(&old, &tmp, -1)))
	{
		if (old[0] == '\0')
			return (NULL);
		swap = tmp;
		tmp = old;
		old = swap;
		//swap = ft_strnchr(tmp, EOF, ft_strlen(tmp));
		//swap[0] = '\0';
		return (tmp);
	}
	//printf("No.2\n");
	return (get_line(fd, &old, size, 0));
}
