/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:11:28 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 22:08:22 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_args	*expand_args(t_args *args)
{
	t_args	*new_args;
	t_args	*temp;

	new_args = NULL;
	temp = args;
	while (temp)
	{
		expand_args_string(temp->argument, &new_args);
		temp = temp->next;
	}
	clear_args_list(args);
	return (new_args);
}

t_redir	*expand_redir(t_redir *redir)
{
	t_redir	*new_redir;
	t_redir	*temp;

	new_redir = NULL;
	temp = redir;
	while (temp)
	{
		expand_redir_string(temp, &new_redir);
		temp = temp->next;
	}
	clear_redir_list(redir);
	return (new_redir);
}

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
