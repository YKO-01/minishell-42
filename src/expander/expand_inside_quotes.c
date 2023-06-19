/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_inside_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:40:08 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 19:08:27 by osajide          ###   ########.fr       */
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

char	*expand_inside_double_quotes(char *s, int *pos)
{
	int		start;
	char	*temp;

	temp = NULL;
	(*pos)++;
	start = *pos;
	while (s[*pos] && s[*pos] != 34)
	{
		if (s[*pos] == '$' && s[*pos + 1] && s[*pos + 1] != 34)
			temp = join_with_free(temp, handle_dollar_sign(s, pos)); // leaks here
		else
			temp = ft_join_char(temp, s[*pos]);
		(*pos)++;
	}
	if (!temp)
		temp = ft_join_char(temp, '\0');
	return (temp);
}
