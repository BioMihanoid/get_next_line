/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 18:10:31 by                   #+#    #+#             */
/*   Updated: 2021/10/25 18:11:09 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*ft_read_static_str(int fd, char *sstr)
{
	char	*buff;
	int		read_check;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	read_check = -1;
	while (!ft_check_endl(sstr) && read_check)
	{
		read_check = read(fd, buff, BUFFER_SIZE);
		if (read_check == -1)
		{
			free (buff);
			return (NULL);
		}
		buff[read_check] = '\0';
		sstr = ft_strjoin(sstr, buff);
	}
	free(buff);
	return (sstr);
}

char	*get_next_line(int fd)
{
	static char	*sstr[FD_MAX_COUNT] = {0};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	sstr[fd] = ft_read_static_str(fd, sstr[fd]);
	if (!sstr[fd])
		return (NULL);
	line = ft_get_line(sstr[fd]);
	if (!ft_strlen(line))
	{
		free(line);
		if (sstr[fd])
		{
			free(sstr[fd]);
			sstr[fd] = NULL;
		}
		return (NULL);
	}
	sstr[fd] = ft_new_static_str(sstr[fd]);
	return (line);
}