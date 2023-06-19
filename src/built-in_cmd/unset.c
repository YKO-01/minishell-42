/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:46:04 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 23:56:08 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

void	if_unset_head(t_env **env)
{
	t_env	*tmp_env;
	t_env	*del;

	tmp_env = *env;
	{
		del = *env;
		if ((*env)->next)
			*env = (*env)->next;
		else
			*env = NULL;
		free(del->content);
		free(del->id);
		free(del);
	}
}

void	unset_var(t_env *tmp_env)
{
	t_env	*del;
	t_env	*temp1;
	t_env	*temp2;

	del = tmp_env;
	temp1 = tmp_env->prev;
	temp2 = tmp_env->next;
	temp1->next = temp2;
	free(del->content);
	free(del->id);
	free(del);
}

void	ft_unset(t_args *args)
{
	t_env	*temp1;
	t_env	*del;
	t_env	*temp2;
	t_env	*tmp_env;

	while (args)
	{
		tmp_env = g_general.env;
		while (tmp_env)
		{
			if (!ft_strncmp(args->argument, g_general.env->id, -1))
			{
				if_unset_head(&g_general.env);
				break ;
			}
			if (!ft_strncmp(args->argument, tmp_env->id, -1))
			{
				unset_var(tmp_env);
				break ;
			}
			tmp_env = tmp_env->next;
		}
		args = args->next;
	}
}
