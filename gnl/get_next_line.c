/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:45:40 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/11 22:14:52 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

// char	*ft_strfree(char *buffer, char *s)
// {
// 	char	*tmp;

// 	tmp = ft_strjoin(buffer, s);
// 	if (!tmp)
// 		return (NULL);
// 	free(buffer);
// 	return (tmp);
// }

// char	*fill_gnl(int fd, char *rest)
// {
// 	int		ret;
// 	char	*buff;

// 	buff = ft_calloc(BUFFER_SIZE + 1, 1);
// 	if (!buff)
// 		return (0);
// 	ret = 1;
// 	while (ret > 0 && !ft_strchr(buff, '\n'))
// 	{
// 		ret = read(fd, buff, BUFFER_SIZE);
// 		if (ret < 0 || (ret == 0 && rest == NULL))
// 			return (free(buff), NULL);
// 		buff[ret] = '\0';
// 		rest = ft_strfree(rest, buff);
// 	}
// 	free(buff);
// 	return (rest);
// }

// char	*ft_line(char *buff)
// {
// 	int		i;
// 	char	*line;

// 	i = 0;
// 	while (buff[i] && buff[i] != '\n')
// 		i++;
// 	line = ft_calloc(i + 2, 1);
// 	if (!line)
// 		return (0);
// 	i = 0;
// 	while (buff[i] && buff[i] != '\n')
// 	{
// 		line[i] = buff[i];
// 		i++;
// 	}
// 	if (buff[i])
// 		line[i++] = '\n';
// 	line[i] = '\0';
// 	return (line);
// }

// void	ft_save(char *rest)
// {
// 	char	*buff;
// 	int		i;
// 	int		j;

// 	buff = rest;
// 	i = 0;
// 	while (buff[i] && buff[i] != '\n')
// 		i++;
// 	if (buff[i] == 0 || (buff[i] == '\n' && buff[i + 1] == 0))
// 	{
// 		rest[0] = 0;
// 		return ;
// 	}
// 	j = 0;
// 	while (buff[++i])
// 	{
// 		rest[j++] = buff[i];
// 	}
// 	rest[j] = 0;
// }

// char	*get_next_line(int fd)
// {
// 	char		*tmp;
// 	static char	rest[BUFFER_SIZE];
// 	char		*line;
// 	int			i;

// 	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
// 		return (rest[0] = 0, NULL);
// 	tmp = ft_calloc(ft_strlen(rest) + 1, 1);
// 	i = -1;
// 	while (rest[++i])
// 		tmp[i] = rest[i];
// 	if (!ft_strchr(tmp, '\n'))
// 		tmp = fill_gnl(fd, tmp);
// 	if (!tmp[0])
// 		return (free(tmp), NULL);
// 	line = ft_line(tmp);
// 	ft_save(tmp);
// 	i = -1;
// 	while (tmp[++i])
// 		rest[i] = tmp[i];
// 	rest[i] = '\0';
// 	free(tmp);
// 	return (line);
// }

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
