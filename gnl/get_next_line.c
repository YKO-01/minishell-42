/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:45:40 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/19 17:10:06 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_reader(int fd, char *buffer)
{
	int		readline;
	char	*s;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	s = malloc(BUFFER_SIZE + 1);
	if (!s)
		return (NULL);
	readline = 1;
	while (readline > 0 && !ft_strchr(buffer, '\n'))
	{
		readline = read(fd, s, BUFFER_SIZE);
		if (readline == -1)
		{
			free(s);
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		s[readline] = '\0';
		buffer = ft_strjoin(buffer, s);
	}
	free(s);
	return (buffer);
}

char	*give_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(i + 2);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*give_rest(char *buffer)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	rest = malloc(ft_strlen(buffer) - i);
	i++;
	j = 0;
	while (buffer[i])
	{
		rest[j] = buffer[i];
		i++;
		j++;
	}
	rest[j] = '\0';
	free(buffer);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_reader(fd, buffer);
	if (!buffer)
		return (NULL);
	line = give_line(buffer);
	buffer = give_rest(buffer);
	return (line);
}
