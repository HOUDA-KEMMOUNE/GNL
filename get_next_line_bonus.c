/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:36:37 by hkemmoun          #+#    #+#             */
/*   Updated: 2024/12/17 12:22:35 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line(char *buffer, char *rest, int fd)
{
	ssize_t		read_ret;
	char		*tmp;

	read_ret = 1;
	while (read_ret > 0)
	{
		read_ret = read(fd, buffer, BUFFER_SIZE);
		if (read_ret == -1)
			return (free(rest), NULL);
		else if (read_ret == 0)
			break ;
		buffer[read_ret] = '\0';
		if (!rest)
			rest = ft_strdup("");
		tmp = rest;
		rest = ft_strjoin(tmp, buffer);
		free(tmp);
		if (!rest)
			return (NULL);
		if (ft_strchr(rest, '\n'))
			break ;
	}
	return (rest);
}

char	*rest_char(char *line)
{
	char	*rest;
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == 0)
		return (NULL);
	if (line[i] == '\n')
		i++;
	rest = ft_substr(line, i, ft_strlen(line) - i);
	if (*rest == 0)
		return (free(rest), NULL);
	line[i] = '\0';
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*rest[MAX_FD];

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = get_line(buffer, rest[fd], fd);
	free(buffer);
	if (!line)
		return (NULL);
	rest[fd] = rest_char(line);
	return (line);
}
