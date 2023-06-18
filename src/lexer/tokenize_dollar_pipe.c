/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_dollar_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:41:17 by osajide           #+#    #+#             */
/*   Updated: 2023/06/11 16:54:55 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"
#include <stdio.h>

int	only_env(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			return (0);
		i++;
	}
	return (1);
}

void	if_dollar_sign(char *line, t_list **lst, int *pos)
{
	int		start;
	char	*temp;

	temp = NULL;
	start = *pos;
	(*pos)++;
	while (line[*pos] && line[*pos] != ' ' && line[*pos] != '|'
		&& line[*pos] != '<' && line[*pos] != '>')
	{
		if (line[*pos] == 34)
			skip_inside_quotes(line, pos, 34);
		else if (line[*pos] == 39)
			skip_inside_quotes(line, pos, 39);
		(*pos)++;
	}
	temp = ft_substr(line, start, *pos);
	if (only_env(temp))
		ft_lstadd_back(lst, ft_lstnew(temp, ENV));
	else
		ft_lstadd_back(lst, ft_lstnew(temp, WORD));
	(*pos)--;
}

void	if_pipe(char *line, t_list **lst, int *pos)
{
	char	*temp;

	temp = NULL;
	temp = ft_strjoin(temp, "|");
	ft_lstadd_back(lst, ft_lstnew(temp, PIPE));
}
