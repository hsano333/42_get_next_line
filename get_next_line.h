/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:17:31 by hsano             #+#    #+#             */
/*   Updated: 2022/07/28 03:51:30 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define MIN_BUFFER_SIZE 512
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>

char	*get_next_line(int fd);
char	*ft_strdup(const char *s1);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strnchr(const char *s, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
size_t	ft_strlen(const char *s);
#endif 
