/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:08:53 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 19:23:12 by osajide          ###   ########.fr       */
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

void	ft_exit(t_args **args)
{
	if ((size_args_list(*args) == 2 || size_args_list(*args) > 2) && !is_num((*args)->next->argument))
	{
		ft_printf(2, "minishell: exit: %s: numeric argument required\n", (*args)->next->argument);
		exit(255);
	}
	else if (size_args_list(*args) > 2 && is_num((*args)->next->argument))
	{
		ft_printf(2, "minishell: exit: too many arguments\n");
		g_general.exit_status = 1;
		return ;
	}
	if ((*args)->next && (*args)->next->argument)
	{
		g_general.exit_status = ft_atoi((*args)->next->argument);
		exit(g_general.exit_status);
	}
	exit(g_general.exit_status);
}
