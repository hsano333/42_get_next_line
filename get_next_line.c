/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:11 by hsano             #+#    #+#             */
/*   Updated: 2022/07/25 21:16:21 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *get_next_line(int fd)
{
	char	**paths;
	char	*read_str;
	int		read_size;

	read_str = (char *)malloc(sizeof(char) * (READ_MAX));
	read_size = read(0, read_str, READ_MAX);
	read_str[read_size - 1] = ' ';
	paths = ft_split(read_str, " ", size);
	free(read_str);
	return (paths);

}
