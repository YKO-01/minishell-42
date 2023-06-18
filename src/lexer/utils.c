/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:47:25 by osajide           #+#    #+#             */
/*   Updated: 2023/06/11 16:50:24 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

int	look_for_char(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_remove_char(char *s, int ascii)
{
	char	*new_char;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == ascii)
			j++;
		i++;
	}
	new_char = malloc((i - j) + 1);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == ascii)
			i++;
		else
			new_char[j++] = s[i++];
	}
	new_char[j] = '\0';
	return (free(s), new_char);
}

void	skip_inside_quotes(char *line, int *pos, int ascii)
{
	(*pos)++;
	while (line[*pos] && line[*pos] != ascii)
		(*pos)++;
}
