/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:00:51 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/18 23:14:41 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

void	execution_commands(t_cmd *cmd, t_env **env)
{
	int	save_fd[2];

	if (general.nbr_cmd == 1 && cmd->args && is_builtin(cmd->args))
	{
		save_fd[0] = dup(STDIN_FILENO);
		save_fd[1] = dup(STDOUT_FILENO);
		cmd->h_fd[0] = -1;
		if (!open_files(*cmd))
		{
			general.exit_status = 1;
			return;
		}
		if (cmd->args->argument)
			builtin_cmd(cmd->args, env);
		dup2(save_fd[0], 0);
		dup2(save_fd[1], 1);
		close(save_fd[0]);
		close(save_fd[1]);
	}
	else
		execute_multiple_cmd(cmd, env);
}

int execute_multiple_cmd(t_cmd *cmd, t_env **env)
{
	int		i;
	int		fd[2];
	int 	prv_fd;
	int		*pid;
	int		file;
	char	*cmd_exec;
	char	**ar;
	unsigned char *st;

	i = -1;
	prv_fd = 0;
	pid = malloc(sizeof(int) * general.nbr_cmd);
	while (++i < general.nbr_cmd)
	{
		if (i < general.nbr_cmd - 1 && pipe(fd) < 0)
			return (printf("an error in create pipe\n"), 0);
		pid[i] = fork();
		if (pid[i] < 0)
			return (printf("an error in create process\n"), 0);
		if (pid[i] == 0)
		{
			if (i < general.nbr_cmd - 1)
			{
				dup2(fd[1], 1);
				close(fd[1]);
			}
			if (i > 0)
			{
				dup2(prv_fd, 0);
				close(fd[0]);
			}
			if (!open_files(cmd[i]))
				exit(1);
			if (cmd[i].args && cmd[i].args->argument)
			{
				if (builtin_cmd(cmd[i].args, env) == 1)
					execute_cmd(&cmd[i], env);
			}
			exit(0);
		}
		else
		{
			if (i > 0)
				close(prv_fd);
			prv_fd = fd[0];
			if (i < general.nbr_cmd - 1)
				close(fd[1]);
			if (cmd[i].redir && cmd[i].redir->type == HEREDOC)
				close(cmd[i].h_fd[0]);
		}
	}
	i = -1;
	while (++i < general.nbr_cmd)
		waitpid(pid[i], &general.exit_status, 0);
	free(pid);
	st = (unsigned char *)&general.exit_status;
	if (st[0])
		general.exit_status = st[0];
	else
		general.exit_status = st[1];
	return (1);
}
