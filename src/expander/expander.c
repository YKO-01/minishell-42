/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:11:28 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 19:02:25 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	expand_cmd(t_cmd *cmd)
{	
	cmd->args = expand_args(cmd->args);
	if (cmd->redir)
		cmd->redir = expand_redir(cmd->redir);
	return (1);
}

t_cmd	*expander(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < g_general.nbr_cmd)
	{
		if (expand_cmd(&cmd[i]) == 0)
			return (NULL);
		i++;
	}
	return (cmd);
}
