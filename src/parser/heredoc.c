/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:58:28 by osajide           #+#    #+#             */
/*   Updated: 2023/06/20 11:03:33 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	check_if_quoted(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_remove_quotes(char *s)
{
	char	*new_s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			j++;
		i++;
	}
	new_s = malloc((i - j) + 1);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			i++;
		else
			new_s[j++] = s[i++];
	}
	new_s[j] = '\0';
	return (new_s);
}

char	*expand_line_read(char *line)
{
	char	*new_line;
	int		i;
	char	*expand;

	i = 0;
	new_line = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			expand = handle_dollar_sign(line, &i);
			new_line = join_with_free(new_line, expand);
			free(expand);
		}
		else
			new_line = ft_join_char(new_line, line[i]);
		i++;
	}
	free(line);
	return (new_line);
}

void	read_heredoc(char *delimiter, int if_quoted, int fd)
{
	char	*line;
	int		in_fd;

	in_fd = dup(0);
	g_general.hrdc_fd = in_fd;
	while (1)
	{
		if (isatty(0))
			ft_printf(1, "> ");
		line = get_next_line(in_fd);
		if (line)
			line = trim_with_free(line, "\n");
		// line = readline("> ");
		if (!line || !ft_strncmp(delimiter, line, -1))
			break ;
		if (!if_quoted)
			line = expand_line_read(line);
		ft_putendl_fd(line, fd);
		free(line);
	}
	dup2(in_fd, 0);
	close(in_fd);
	close(g_general.hrdc_fd);
	free(line);
}

void	ft_heredoc(t_cmd *cmd)
{
	char	*line;
	char	*expand_del;
	int		if_quoted;
	int		fd;
	t_redir	*tmp;

	tmp = cmd->redir;
	while (tmp)
	{
		if (g_general.hrdc_fd == -2)
			break;
		if (tmp->type == HEREDOC)
		{
			if_quoted = check_if_quoted(tmp->file);
			expand_del = ft_remove_quotes(tmp->file);
			pipe(cmd->h_fd);
			read_heredoc(expand_del, if_quoted, cmd->h_fd[1]);
			free(expand_del);
			close(cmd->h_fd[1]);
		}
		tmp = tmp->next;
	}
}
