/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:01:16 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/19 17:18:24 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

t_general	g_general;

int	main(int ac, char **av, char **env)
{
	t_env	*env_lst;
	t_list	*lst;

	(void)ac;
	(void)av;
	handle_signals();
	lst = NULL;
	env_lst = convert_env_to_list(env);
	minishell(&env_lst, &lst);
	clear_env_lst(env_lst);
	return (0);
}
