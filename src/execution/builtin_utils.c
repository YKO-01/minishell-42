/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:05:17 by osajide           #+#    #+#             */
/*   Updated: 2023/06/17 15:58:36 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		is_builtin(t_args *args)
{
	if (args->argument)
	{
		if (!ft_strncmp(args->argument, "cd", -1))
			return (1);
		if (!ft_strncmp(args->argument, "pwd", -1))
			return (1);
		if (!ft_strncmp(args->argument, "export", -1))
			return (1);
		if (!ft_strncmp(args->argument, "echo", -1))
			return (1);
		if (!ft_strncmp(args->argument, "env", -1))
			return (1);
		if (!ft_strncmp(args->argument, "unset", -1))
			return (1);
		if (!ft_strncmp(args->argument, "exit", -1))
			return (1);
	}
	return (0);
}