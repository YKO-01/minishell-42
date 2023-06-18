/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:20:28 by osajide           #+#    #+#             */
/*   Updated: 2023/06/13 18:35:34 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clear_args_list(t_args *args)
{
	t_args	*tmp;
	
	while (args)
	{
		tmp = args;
		args = args->next;
		free(tmp->argument);
		free(tmp);
	}
}

void	clear_redir_list(t_redir *redir)
{
	t_redir	*tmp;
	
	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp->file);
		free(tmp);
	}
}
