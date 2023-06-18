/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:03:24 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/18 22:48:48 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		open_files(t_cmd cmd)
{
	int	fd_in;
	int	fd_out;
	char	*hrdc;
	char	*line;

	while (cmd.redir)
	{
		if (cmd.redir->type == REDIR_IN)
		{
			if (handle_file_in(cmd.redir))
			{
				fd_in = open(cmd.redir->file, O_RDONLY);
				if (fd_in < 0)
					return (0);
				dup2(fd_in, 0);
				close(fd_in);
			}
			else 
				return (0);
		}
		else if (cmd.redir->type == REDIR_OUT || cmd.redir->type == APPEND_REDIR)
		{
			if (handle_file_out(cmd.redir))
			{
				if (cmd.redir->type == REDIR_OUT)
					fd_out = open(cmd.redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				else
					fd_out = open(cmd.redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd_out < 0)
					return (0);
				dup2(fd_out, 1);
				close(fd_out);
			}
			else 
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

void    execute_cmd(t_cmd *cmd, t_env **env)
{
	char	*cmd_exec;
	char	**ar;
	char	**new_env;

	if (cmd->args)
	{
		new_env = dup_lstenv(*env);
		if (!new_env)
		{
			ft_printf(2, "minishell: %s: No such file or directory\n", cmd->args->argument);
			exit(127);
		}
		cmd_exec = get_path_cmd(cmd, new_env);
		if (!cmd_exec)
		{
			free_2d_array(new_env);
			exit(127);
		}
		ar = get_new_arg(cmd);
		if (execve(cmd_exec, ar, new_env) < 0)
		{
			free(cmd_exec);
			free_2d_array(new_env);
			free_2d_array(ar);
			exit(1);
		}
	}
}
