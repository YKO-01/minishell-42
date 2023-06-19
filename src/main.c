/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:01:16 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/19 19:44:50 by osajide          ###   ########.fr       */
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
	g_general.env = NULL;
	g_general.env = convert_env_to_list(env);
	minishell(&lst);
	clear_env_lst();
	return (0);
}
