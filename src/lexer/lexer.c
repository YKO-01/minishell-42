/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:10:49 by osajide           #+#    #+#             */
/*   Updated: 2023/06/06 15:19:00 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

void	loop_on_input(char *line, t_list **lst)
{
	int		i;

	i = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == 32 || line[i] == '\t'))
			i++;
		if (line[i] == 39)
			if_single_quote(line, lst, &i);
		else if (line[i] == 34)
			if_double_quote(line, lst, &i);
		else if (line[i] == '$')
			if_dollar_sign(line, lst, &i);
		else if (line[i] == '|')
			if_pipe(line, lst, &i);
		else if (line[i] == '<')
			input_redirection(line, lst, &i);
		else if (line[i] == '>')
			output_redirection(line, lst, &i);
		else
			if_string(line, lst, &i);
		i++;
	}
}
