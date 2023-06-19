/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:48:21 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 19:06:29 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clear_lst(t_list *lst)
{
	t_list	*cur;

	if (!lst)
		return ;
	while (lst)
	{
		cur = lst;
		lst = lst->next;
		free(cur->data->content);
		free(cur->data);
		free(cur);
	}
}

void	clear_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < g_general.nbr_cmd)
	{
		clear_args_list(cmd[i].args);
		clear_redir_list(cmd[i].redir);
	}
	free(cmd);
}

void	clear_env_lst(void)
{
	t_env	*tmp_env;

	tmp_env = g_general.env;
	while (tmp_env)
	{
		free(tmp_env->id);
		free(tmp_env->content);
		tmp_env = tmp_env->next;
	}
}
