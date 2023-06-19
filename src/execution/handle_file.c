/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:20:45 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/19 19:57:47 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_file_out(t_redir *redir)
{
	if (redir->ambiguous == IS_AMBIGUOUS)
		return (g_general.exit_status = 1, ft_printf(2, "minishell: %s: ambiguous redirect\n", redir->file), 0);
	else if (redir->ambiguous == NOT_AMBIGUOUS)
		return (g_general.exit_status = 1, ft_printf(2, "minishell: No such file or directory\n"), 0);
	if (!access(redir->file, F_OK))
	{
		if (access(redir->file, W_OK) < 0)
			return (g_general.exit_status = 1, ft_printf(2, "minishell: %s: Permission denied\n", redir->file), 0);
	}
	return (1);
}

int handle_file_in(t_redir *redir)
{
	if (redir->ambiguous == IS_AMBIGUOUS)
		return (g_general.exit_status = 1, ft_printf(2, "minishell: %s: ambiguous redirect\n", redir->file), 0);
	if (access(redir->file, F_OK) < 0)
		return (g_general.exit_status = 1, ft_printf(2, "minishell: %s: No such file or directory\n", redir->file), 0);
	if (access(redir->file, R_OK) < 0)
		return (g_general.exit_status = 1, ft_printf(2, "minishell: %s: Permission denied\n", redir->file), 0);
	return (1);
}

int	open_file_in(t_redir *redir)
{
	int fd_in;
	if (handle_file_in(redir))
	{
		fd_in = open(redir->file, O_RDONLY);
		if (fd_in < 0)
			return (0);
		dup2(fd_in, 0);
		close(fd_in);
		return (1);
	}
	return (0);
}

int	open_file_out_and_append(t_redir *redir)
{
	int	fd_out;
	if (handle_file_out(redir))
	{
		if (redir->type == REDIR_OUT)
			fd_out = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd_out = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_out < 0)
			return (0);
		dup2(fd_out, 1);
		close(fd_out);
		return (1);
	}
	return (0);
}

int		open_files(t_cmd cmd)
{
	char	*hrdc;
	char	*line;

	while (cmd.redir)
	{
		if (cmd.redir->type == REDIR_IN)
		{
			if (!open_file_in(cmd.redir))
				return (0);
		}
		else if (cmd.redir->type == REDIR_OUT || cmd.redir->type == APPEND_REDIR)
		{
			if(!open_file_out_and_append(cmd.redir))
				return (0);
		}
		else if (cmd.redir->type == HEREDOC)
		{
			dup2(cmd.h_fd[0], 0);
			close(cmd.h_fd[0]);
		}
		cmd.redir = cmd.redir->next;
	}
	return (1);
}