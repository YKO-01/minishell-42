/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:05:17 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 22:45:35 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	args_list_size(t_args *args)
{
	t_args	*tmp;
	int		size;

	size = 0;
	tmp = args;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}

int	env_list_size(t_env *env)
{
	t_env	*tmp;
	int		size;

	size = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}

int	is_builtin(t_args *args)
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
