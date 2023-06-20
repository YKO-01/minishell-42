/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:00:51 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/20 11:25:14 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execution_commands(t_cmd *cmd)
{
	int	save_fd[2];

	if (g_general.nbr_cmd == 1 && cmd->args && is_builtin(cmd->args))
	{
		save_fd[0] = dup(STDIN_FILENO);
		save_fd[1] = dup(STDOUT_FILENO);
		cmd->h_fd[0] = -1;
		if (!open_files(*cmd))
		{
			g_general.exit_status = 1;
			return ;
		}
		if (cmd->args->argument)
			builtin_cmd(cmd->args);
		dup2(save_fd[0], 0);
		dup2(save_fd[1], 1);
		close(save_fd[0]);
		close(save_fd[1]);
	}
	else
		execute_multiple_cmd(cmd);
}

void	exec_child_pro(t_cmd *cmd, t_fd *file_d, int i)
{
	signal(SIGQUIT, SIG_DFL);
	if (i < g_general.nbr_cmd - 1)
	{
		dup2(file_d->fd[1], 1);
		close(file_d->fd[1]);
	}
	if (i > 0)
	{
		dup2(file_d->prv_fd, 0);
		close(file_d->prv_fd);
	}
	if (!open_files(*cmd))
		exit(1);
	if (cmd->args && cmd->args->argument)
	{
		if (builtin_cmd(cmd->args) == 1)
			execute_cmd(cmd);
	}
	exit(0);
}

void	close_file_parent(t_cmd *cmd, t_fd *file_d, int i)
{
	if (i > 0)
		close(file_d->prv_fd);
	file_d->prv_fd = file_d->fd[0];
	if (i < g_general.nbr_cmd - 1)
		close(file_d->fd[1]);
	if (cmd->redir && cmd->redir->type == HEREDOC)
		close(cmd->h_fd[0]);
}

int	loop_execute_cmd(t_cmd *cmd, int *pid)
{
	t_fd	file_d;
	int		i;

	file_d.prv_fd = -1;
	file_d.fd[1] = -1;
	file_d.fd[0] = -1;
	i = -1;
	while (++i < g_general.nbr_cmd)
	{
		g_general.sig_flag = 1;
		if (i < g_general.nbr_cmd - 1 && pipe(file_d.fd) < 0)
			return (printf("an error in create pipe\n"), 0);
		pid[i] = fork();
		if (pid[i] < 0)
			return (printf("an error in create process\n"), 0);
		if (pid[i] == 0)
			exec_child_pro(&cmd[i], &file_d, i);
		else
			close_file_parent(&cmd[i], &file_d, i);
	}
	return (1);
}

int	execute_multiple_cmd(t_cmd *cmd)
{
	int				i;
	int				*pid;
	unsigned char	*st;

	pid = malloc(sizeof(int) * g_general.nbr_cmd);
	if (!pid)
		return (0);
	loop_execute_cmd(cmd, pid);
	i = -1;
	while (++i < g_general.nbr_cmd)
		waitpid(pid[i], &g_general.exit_status, 0);
	free(pid);
	st = (unsigned char *)&g_general.exit_status;
	if (st[0])
		g_general.exit_status = st[0] + 128;
	else
		g_general.exit_status = st[1];
	return (1);
}
