/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:06:28 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/17 00:00:33 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	number_of_quotes(char *line, int ascii)
{
	int	i;
	int	number_of_quotes;

	i = 0;
	number_of_quotes = 0;
	while (line[i])
	{
		if (line[i] == ascii)
			number_of_quotes++;
		i++;
	}
	return (number_of_quotes);
}

int	next_quote(char *line, int *i, int ascii)
{
	int	count;

	count = 1;
	while (line[*i])
	{
		if (line[*i] == ascii)
			return (count++, count);
		(*i)++;
	}
	return (count);
}

int	check_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != 34 && line[i] != 39)
		i++;
	if (!line[i])
		return (1);
	while (line[i])
	{
		if (line[i] == 34)
		{
			i++;
			if (next_quote(line, &i, 34) == 1)
				return (general.exit_status = 258 ,ft_printf(2, "minishell: unexpected EOF while looking for matching\n"), 0);
		}
		else if (line[i] == 39)
		{
			i++;
			if (next_quote(line, &i, 39) == 1)
				return (general.exit_status = 258, ft_printf(2, "minishell: unexpected EOF while looking for matching\n"), 0);
		}
		i++;
	}
	return (1);
}
