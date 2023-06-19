/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:20:45 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/19 17:12:22 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

int	handle_file_out(t_redir *redir)
{
	if (redir->ambiguous == IS_AMBIGUOUS)
		return (g_general.exit_status = 1, ft_printf(2, "minishell: %s: ambiguous redirect\n", redir->file), 0);
	else if (redir->ambiguous == NOT_AMBIGUOUS)
		return (g_general.exit_status = 1, ft_printf(2, "minishell: No such file or directory\n"), 0);
	if (!access(redir->file, F_OK))
	{
		if (access(redir->file, W_OK) < 0)
			return (g_general.exit_status = 1, ft_printf(2, "minishell: %s: Permission denied\n", redir->file), 0);
	}
	return (1);
}

int handle_file_in(t_redir *redir)
{
	if (redir->ambiguous == IS_AMBIGUOUS)
		return (g_general.exit_status = 1, ft_printf(2, "minishell: %s: ambiguous redirect\n", redir->file), 0);
	if (access(redir->file, F_OK) < 0)
		return (g_general.exit_status = 1, ft_printf(2, "minishell: %s: No such file or directory\n", redir->file), 0);
	if (access(redir->file, R_OK) < 0)
		return (g_general.exit_status = 1, ft_printf(2, "minishell: %s: Permission denied\n", redir->file), 0);
	return (1);
}
