/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:58:50 by osajide           #+#    #+#             */
/*   Updated: 2023/06/18 21:56:19 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	expand_args_string(char *s, t_env *env_lst, t_args **new_args)
{
	int		i;
	char	*temp;
	char	*var;
	char	**split;
	int		to_join;

	i = 0;
	temp = NULL;
	var = NULL;
	if (!s)
		return ;
	while (s[i])
	{
		to_join = 1;
		if (s[i] == 39)
		{
			char *h = expand_inside_single_quotes(s, &i);
			temp =  join_with_free(temp, h);
			free(h);
		}
		else if (s[i] == 34)
		{
			char *h = expand_inside_double_quotes(s, &i, env_lst);
			temp = join_with_free(temp, h);
			free(h);
		}
		else if (s[i] == '$')
		{
			var = handle_dollar_sign(s, &i, env_lst);
			if (s[i + 1] == '$')
			{
				i++;
				char *h = handle_dollar_sign(s, &i, env_lst);
				var = join_with_free(var, h);
				free(h);
			}
			if (!temp && split_word_count(var, "\t ") <= 1)
				var = trim_with_free(var, "\t ");
			else if (split_word_count(var, "\t ") > 1)
			{
				to_join = 0;
				replace_var_in_args_list(temp, var, new_args);
			}
			if (to_join && *var)
				temp = join_with_free(temp, var);
			free(var);
		}
		else
			temp = ft_join_char(temp, s[i]);
		i++;
	}
	add_args_node_back(new_args, new_args_node(temp));
}

t_args	*expand_args(t_args *args, t_env *env_lst)
{
	t_args	*new_args;
	t_args	*temp;
	
	new_args = NULL;
	temp = args;
	while (temp)
	{
		expand_args_string(temp->argument, env_lst, &new_args);
		temp = temp->next;
	}
	clear_args_list(args);
	return (new_args);
}