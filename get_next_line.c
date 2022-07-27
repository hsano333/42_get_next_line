/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:11 by hsano             #+#    #+#             */
/*   Updated: 2022/07/27 12:22:01 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	parse_line(char **p, char **old,  ssize_t read_num,ssize_t i)
{
	char	*lf;

	//(*p)[i + read_num] = '\0';
	
	lf = ft_memchr(*p, '\n', read_num);
	//printf("i=%zu,read_num=%zu, p=%s,lf=%s, p[0]=%d,lf[0]=%d,%d\n",i,read_num, *p,lf,*p[0],lf[0],'\n');
	if (lf)
	{
		//printf("test No.1 lf=%s\n",lf);
		if (lf[1] != '\0')
			*old = ft_strdup(lf + 1);
		else
			*old = NULL;
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
	else if (i != -1 && read_num < BUFFER_SIZE)
	{
		/*
		lf = ft_memchr(*p, EOF, read_num);
		if (lf != NULL)
			lf[1] = '\0';
			*/
		//printf("test No.3 i=%zu,read_num=%zu,lf=%s,p=%s\n",i,read_num,lf,*p);
		if (i == 0)
		{
			//printf("test No.4\n");
			//printf("");
			free(*p);
			*p = NULL;
		}
		else
		{

			(*p)[i] = '\0';
		}
		//*p = NULL;
		*old = NULL;
		return (true);
	}
	//printf("test No.5\n");
	return (false);
}

char	*mange_memory(char *old, size_t size)
{
	size_t	old_len;
	char	*p;

	//printf("mangage_memory No.1 old_len=%zu\n",ft_strlen(old));
	old_len = ft_strlen(old);
	//printf("mangage_memory No.2 old_len=%zu\n",ft_strlen(old));
	//printf("old_len=%zu\n",old_len);
	p = malloc(size + old_len + 1);
	//p[size + old_len + 1] = '\0';
	//printf("mangage_memory No.3 old_len=%zu\n",ft_strlen(old));
	if (!p)
	{
		if (old)
			free(old);
		return (NULL);
	}
	//printf("mangage_memory No.4 old_len=%zu\n",ft_strlen(old));
	p = ft_strcpy(p, old);
	//printf("mangage_memory No.5 old_len=%zu\n",ft_strlen(old));
	if (old)
		free(old);
	//printf("mangage_memory No.6 old_len=%zu\n",ft_strlen(old));
	return (p);

}

char	*get_line(int fd, char **old, size_t size, size_t i)
{
	//size_t	i;
	char	*p;
	size_t	old_len;
	ssize_t	read_num;

	//printf("start get_line No.1 old_len=%zu old=\n",ft_strlen(*old));
	p = mange_memory(*old, size);
	//printf("start get_line No.2 old_len=%zu old=%s\n",ft_strlen(*old),p);
	if (!p)
		return (NULL);
	//printf("start get_line No.3 old_len=%zu old=%s\n",ft_strlen(*old),p);
	old_len = ft_strlen(*old);
	//printf("start get_line No.4 old_len=%zu old=%s\n",ft_strlen(*old),p);
	//i = old_len;
	read_num = BUFFER_SIZE;
	while (read_num == BUFFER_SIZE)
	{
		read_num = read(fd, &(p[i]), BUFFER_SIZE);
		//printf("read p=%s,i=%zu\n",p,i);
		i += read_num;
		if (parse_line(&p, old, read_num, i))
			break;
		if (i >= size + old_len - BUFFER_SIZE)
		{
			p[i] = '\0';
			//printf("start get_line No.3 old_len=%zu \n",ft_strlen(p));
			return (get_line(fd, &p, size, i));
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
	if (old != NULL && parse_line(&old, &tmp, ft_strlen(old), -1))
	{
		//printf("swap No.1 old=%s, tmp=%s\n",old,tmp);
		swap = tmp;
		tmp = old;
		old = swap;
		return tmp;
	}
	//printf("get_line\n");
	return (get_line(fd, &old, size, 0));
}

