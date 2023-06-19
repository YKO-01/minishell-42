/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:10:14 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 22:48:56 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_args *args)
{
	t_env	*tmp;

	if (!g_general.env)
		return ;
	tmp = g_general.env;
	if (!args)
	{
		while (tmp)
		{
			if (tmp->content)
				printf("%s=%s\n", tmp->id, tmp->content);
			tmp = tmp->next;
		}	
	}
	else
		ft_printf(2, "minishell: %s: No such file or directory\n",
			args->argument);
}
