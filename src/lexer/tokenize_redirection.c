/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 00:01:48 by osajide           #+#    #+#             */
/*   Updated: 2023/06/11 16:55:36 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

void	input_redirection(char *line, t_list **lst, int *pos)
{
	char	*temp;

	temp = NULL;
	if (line[*pos + 1] == '<')
	{
		temp = ft_substr(line, *pos, *pos + 2);
		ft_lstadd_back(lst, ft_lstnew(temp, HEREDOC));
		(*pos)++;
	}
	else
	{
		temp = ft_strjoin(temp, "<");
		ft_lstadd_back(lst, ft_lstnew(temp, REDIR_IN));
	}
}

void	output_redirection(char *line, t_list **lst, int *pos)
{
	char	*temp;

	temp = NULL;
	if (line[*pos + 1] == '>')
	{
		temp = ft_substr(line, *pos, *pos + 2);
		ft_lstadd_back(lst, ft_lstnew(temp, APPEND_REDIR));
		(*pos)++;
	}
	else
	{
		temp = ft_strjoin(temp, ">");
		ft_lstadd_back(lst, ft_lstnew(temp, REDIR_OUT));
	}
}
