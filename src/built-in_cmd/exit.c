/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:08:53 by osajide           #+#    #+#             */
/*   Updated: 2023/06/14 20:05:17 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	size_args_list(t_args *args)
{
	int	i;

	i = 0;
	while (args)
	{
		i++;
		args = args->next;
	}
	return (i);
}

int	is_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_args **args, t_env **env_lst)
{
	if ((size_args_list(*args) == 2 || size_args_list(*args) > 2) && !is_num((*args)->next->argument))
	{
		ft_printf(2, "minishell: exit: %s: numeric argument required\n", (*args)->next->argument);
		exit(255);
	}
	else if (size_args_list(*args) > 2 && is_num((*args)->next->argument))
	{
		ft_printf(2, "minishell: exit: too many arguments\n");
		general.exit_status = 1;
		return ;
	}
	if ((*args)->next && (*args)->next->argument)
	{
		general.exit_status = ft_atoi((*args)->next->argument);
		exit(general.exit_status);
	}
	exit(general.exit_status);
}
