/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:58:28 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 17:14:56 by osajide          ###   ########.fr       */
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

char	*expand_line_read(char *line, t_env *env_lst)
{
	char	*new_line;
	int		i;
	
	i = 0;
	new_line = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			char *j = handle_dollar_sign(line, &i, env_lst);
			new_line = join_with_free(new_line, j);
			free(j);
		}
		else
			new_line = ft_join_char(new_line, line[i]);
		i++;
	}
	free(line);
	// while (1);
	return (new_line);
}

void	read_herdoc(t_cmd *cmd, t_env *env_lst)
{
	char	*line;
	char	*expand_del;
	int		if_quoted;
	int 	fd;
	t_redir	*tmp;
	
	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			if_quoted = check_if_quoted(tmp->file);
			expand_del = ft_remove_quotes(tmp->file);
			pipe(cmd->h_fd);
			while (1)
			{
				if (isatty(0))
					ft_printf(1, "> ");
				line = get_next_line(0);
				if (line)
					line = trim_with_free(line, "\n");
				// line = readline("> ");
				if (!line || !ft_strncmp(expand_del, line, -1))
					break;
				if (!if_quoted)
					line = expand_line_read(line, env_lst);
				ft_putendl_fd(line, cmd->h_fd[1]);
				free(line);
			}
			if (line)
				free(line);
			free(expand_del);
			close(cmd->h_fd[1]);
		}
		tmp = tmp->next;
	}
}
