/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:58:50 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 20:34:18 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>

char	*dollar_sign_case(t_args **new_args, char *s, int *pos, char *before)
{
	char	*var;
	char	*temp1;
	int		to_join;

	to_join = 1;
	var = handle_dollar_sign(s, pos);
	if (s[*pos + 1] == '$')
	{
		(*pos)++;
		temp1 = handle_dollar_sign(s, pos);
		var = join_with_free(var, temp1);
		free(temp1);
	}
	if (!before && split_word_count(var, "\t ") <= 1)
		var = trim_with_free(var, "\t ");
	else if (split_word_count(var, "\t ") > 1)
	{
		to_join = 0;
		replace_var_in_args_list(before, var, new_args);
	}
	if (to_join && *var)
		before = join_with_free(before, var);
	free(var);
	return (before);
}

char	*signle_quote_case(char *s, int *pos, char *before)
{
	char	*temp;

	temp = expand_inside_single_quotes(s, pos);
	before = join_with_free(before, temp);
	free(temp);
	return (before);
}

char	*double_quotes_case(char *s, int *pos, char *before)
{
	char	*temp;

	temp = expand_inside_double_quotes(s, pos);
	before = join_with_free(before, temp);
	free(temp);
	return (before);
}

void	expand_args_string(char *s, t_args **new_args)
{
	int		i;
	char	*temp;
	int		to_join;

	i = 0;
	temp = NULL;
	if (!s)
		return ;
	while (s[i])
	{
		to_join = 1;
		if (s[i] == 39)
			temp = signle_quote_case(s, &i, temp);
		else if (s[i] == 34)
			temp = double_quotes_case(s, &i, temp);
		else if (s[i] == '$')
			temp = dollar_sign_case(new_args, s, &i, temp);
		else
			temp = ft_join_char(temp, s[i]);
		i++;
	}
	add_args_node_back(new_args, new_args_node(temp));
}

t_args	*expand_args(t_args *args)
{
	t_args	*new_args;
	t_args	*temp;

	new_args = NULL;
	temp = args;
	while (temp)
	{
		expand_args_string(temp->argument, &new_args);
		temp = temp->next;
	}
	clear_args_list(args);
	return (new_args);
}
