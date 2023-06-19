/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_inside_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:40:08 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 19:49:00 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

char	*expand_inside_double_quotes(char *s, int *pos)
{
	int		start;
	char	*temp;
	char	*var;

	temp = NULL;
	var = NULL;
	(*pos)++;
	start = *pos;
	while (s[*pos] && s[*pos] != 34)
	{
		if (s[*pos] == '$' && s[*pos + 1] && s[*pos + 1] != 34)
		{
			var = handle_dollar_sign(s, pos);
			temp = join_with_free(temp, var);
			free(var);
		}
		else
			temp = ft_join_char(temp, s[*pos]);
		(*pos)++;
	}
	if (!temp)
		temp = ft_join_char(temp, '\0');
	return (temp);
}
