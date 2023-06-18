/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:01:16 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/13 22:19:21 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	minishell(env);
	// general.eexit_status = 2;
	return (0);
}
