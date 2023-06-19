/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:03:24 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/19 19:55:02 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_cmd(t_cmd *cmd)
{
	char	*cmd_exec;
	char	**ar;
	char	**new_env;

	new_env = dup_lstenv();
	if (!new_env)
	{
		ft_printf(2, "minishell: %s: No such file or directory\n",
			cmd->args->argument);
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
