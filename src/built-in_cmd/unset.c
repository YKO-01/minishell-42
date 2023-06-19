/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:46:04 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 19:40:01 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

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
				del = tmp_env;
				if (tmp_env->next)
					tmp_env = tmp_env->next;
				else
					tmp_env = NULL;
				free(del->content);
				free(del->id);
				free(del);
				break ;
			}
			if (!ft_strncmp(args->argument, tmp_env->id, -1))
			{
				del = tmp_env;
				temp1 = tmp_env->prev;
				temp2 = tmp_env->next;
				temp1->next = temp2;
				free(del->content);
				free(del->id);
				free(del);
				break ;
			}
			tmp_env = tmp_env->next;
		}
		args = args->next;
	}
}
