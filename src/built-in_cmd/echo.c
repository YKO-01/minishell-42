/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:13:36 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/19 22:46:14 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

int	compare_char(char *s, char c, int len)
{
	int	i;

	i = 0;
	while (s[i] && i < len)
	{
		if (s[i] != c)
			return (0);
		i++;
	}
	return (1);
}

void	print_echo_args(t_args *args)
{
	while (args)
	{
		if (args->argument && args->argument[0] != '\0')
		{
			ft_printf(1, "%s", args->argument);
			if ((args->next && args->next->argument)
				|| (args->next && !args->next->argument
					&& args->next->next))
				ft_printf(1, " ");
		}
		args = args->next;
	}
}

void	ft_echo(t_args *args)
{
	char	*temp;
	int		compare;

	compare = 0;
	if (!args)
	{
		ft_printf(1, "\n");
		return ;
	}
	if (args)
	{
		while (args && args->argument && args->argument[0] == '-'
			&& compare_char(args->argument + 1, 'n',
				ft_strlen(args->argument + 1)))
		{
			temp = args->argument;
			args = args->next;
		}
		if (args)
			print_echo_args(args);
	}
	if (!compare_char(temp + 1, 'n', ft_strlen(temp + 1)))
		ft_printf(1, "\n");
	g_general.exit_status = 0;
}
