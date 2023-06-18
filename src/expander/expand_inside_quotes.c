/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_inside_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:40:08 by osajide           #+#    #+#             */
/*   Updated: 2023/06/17 15:55:12 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

char	*expand_inside_single_quotes(char *s, int *pos)
{
	char	*temp;
	int		start;

	temp = NULL;
	(*pos)++;
	start = *pos;
	while (s[*pos] && s[*pos] != 39)
		(*pos)++;
	temp = ft_substr(s, start, *pos);
	return (temp);
}

char	*expand_inside_double_quotes(char *s, int *pos, t_env *env_lst)
{
	int		start;
	char	*temp;

	temp = NULL;
	(*pos)++;
	start = *pos;
	while (s[*pos] && s[*pos] != 34)
	{
		if (s[*pos] == '$' && s[*pos + 1] && s[*pos + 1] != 34)
			temp = ft_strjoin(temp, handle_dollar_sign(s, pos, env_lst));
		else
			temp = ft_join_char(temp, s[*pos]);
		(*pos)++;
	}
	if (!temp)
		temp = ft_join_char(temp, '\0');
	return (temp);
}
