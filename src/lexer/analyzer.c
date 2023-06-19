/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:00:10 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 18:03:26 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_syntax_error(void)
{
	g_general.exit_status = 258;
	ft_putstr_fd("minishell: syntax error\n", 2);
}

int	check_and_print_error(t_list *temp)
{
	if (temp->data->token == PIPE)
	{
		if (!temp->prev || !temp->next || temp->next->data->token == PIPE)
			return (print_syntax_error(), 1);
	}
	else if (temp->data->token == REDIR_OUT
		|| temp->data->token == APPEND_REDIR)
	{
		if (!temp->next || (temp->next->data->token != WORD
				&& temp->next->data->token != ENV))
			return (print_syntax_error(), 1);
	}
	else if (temp->data->token == REDIR_IN || temp->data->token == HEREDOC)
	{
		if (!temp->next || (temp->next->data->token != WORD
				&& temp->next->data->token != ENV))
			return (print_syntax_error(), 1);
	}
	return (0);
}

int	analyzer(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		if (check_and_print_error(temp))
		{
			clear_lst(lst);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}
