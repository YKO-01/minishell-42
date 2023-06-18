/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 22:44:57 by osajide           #+#    #+#             */
/*   Updated: 2023/06/11 16:53:39 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"
#include <stdio.h>

void	check_inside_double_quotes(char *temp, char
	*line, t_list **lst, int *pos)
{
	int		start;
	char	*temp1;

	temp1 = NULL;
	start = *pos;
	(*pos)++;
	while (line[*pos] && line[*pos] != 34)
		(*pos)++;
	temp1 = ft_substr(line, start, *pos + 1);
	if (look_for_char(temp1))
	{
		ft_lstadd_back(lst, ft_lstnew(temp, WORD));
		ft_lstadd_back(lst, ft_lstnew(temp1, WORD));
	}
	else
	{
		temp1 = ft_remove_char(temp1, 34);
		ft_lstadd_back(lst, ft_lstnew(ft_strjoin(temp, temp1), WORD));
	}
}

char	*handle_quote(t_list **lst, char *line, int *pos, int ascii)
{
	char	*temp;
	int		start;

	start = *pos;
	(*pos)++;
	while (line[*pos] && line[*pos] != ascii)
		(*pos)++;
	temp = ft_substr(line, start, *pos + 1);
	return (temp);
}

void	if_string(char *line, t_list **lst, int *pos)
{
	int		start;
	char	*temp;

	temp = NULL;
	start = *pos;
	while (line[*pos] && line[*pos] != ' ' && line[*pos] != '\t'
		&& line[*pos] != '<' && line[*pos] != '>' && line[*pos] != '|')
	{
		if (line[*pos] == 34)
			skip_inside_quotes(line, pos, 34);
		else if (line[*pos] == 39)
			skip_inside_quotes(line, pos, 39);
		(*pos)++;
	}
	(*pos)--;
	temp = ft_substr(line, start, *pos + 1);
	if (temp && *temp)
		ft_lstadd_back(lst, ft_lstnew(temp, WORD));
}

void	if_single_quote(char *line, t_list **lst, int *pos)
{
	char	*temp;
	int		start;

	temp = NULL;
	temp = handle_quote(lst, line, pos, 39);
	(*pos)++;
	if (line[*pos] && line[*pos] != ' ' && line[*pos] != '\t')
	{
		start = *pos;
		while (line[*pos] && line[*pos] != '|' && line[*pos] != '<'
			&& line[*pos] != '>' && line[*pos] != ' ')
		{
			if (line[*pos] == 34)
				skip_inside_quotes(line, pos, 34);
			else if (line[*pos] == 39)
				skip_inside_quotes(line, pos, 39);
			(*pos)++;
		}
		temp = ft_strjoin(temp, ft_substr(line, start, *pos));
	}
	ft_lstadd_back(lst, ft_lstnew(temp, WORD));
	(*pos)--;
}

void	if_double_quote(char *line, t_list **lst, int *pos)
{
	char	*temp;
	int		start;

	temp = NULL;
	temp = handle_quote(lst, line, pos, 34);
	(*pos)++;
	if (line[*pos] && line[*pos] != ' ' && line[*pos] != '\t')
	{
		start = *pos;
		while (line[*pos] && line[*pos] != '|' && line[*pos] != '<'
			&& line[*pos] != '>' && line[*pos] != ' ')
		{
			if (line[*pos] == 34)
				skip_inside_quotes(line, pos, 34);
			else if (line[*pos] == 39)
				skip_inside_quotes(line, pos, 39);
			(*pos)++;
		}
		temp = ft_strjoin(temp, ft_substr(line, start, *pos));
	}
	ft_lstadd_back(lst, ft_lstnew(temp, WORD));
	(*pos)--;
}
