/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:17:23 by hsano             #+#    #+#             */
/*   Updated: 2022/07/26 19:01:45 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	tmp;

	i = 0;
	p = (unsigned char *)s;
	tmp = (unsigned char)c;
	while (i < n)
	{
		if (*(p++) == tmp)
			return ((void *)&(s[i]));
		i++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while ((*(s++)))
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*p;
	char	*bk;

	size = ft_strlen(s1);
	p = (char *)malloc(size + 1);
	bk = p;
	if (p == NULL)
		return (NULL);
	p[size] = '\0';
	while (size--)
		*(p++) = *(s1++);
	return (bk);
}
