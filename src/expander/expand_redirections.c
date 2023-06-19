/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:26:45 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 19:07:42 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

char	*replace_spaces(char *var)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (var[i] =='\t' || var[i] == ' ')
			var[i] = 6;
		i++;
	}
	return (var);
}

int	expand_redir_string(t_redir *redir, t_redir **new_redir)
{
	int		i;
	char	*temp;
	char	*var;
	int		is_dollar;
	int		is_ambiguous;

	i = 0;
	is_ambiguous = NOTHING;
	temp = NULL;
	var = NULL;
	if (redir->type != HEREDOC)
	{
		while (redir->file[i])
		{
			is_dollar = 0;
			if (redir->file[i] == 39)
				temp =  join_with_free(temp, expand_inside_single_quotes(redir->file, &i));
			else if (redir->file[i] == 34)
				temp = join_with_free(temp, expand_inside_double_quotes(redir->file, &i));
			else if (redir->file[i] == '$')
			{
				var = handle_dollar_sign(redir->file, &i);
				if (!temp && !var[0])
					is_dollar = 1;
				var = replace_spaces(var);
				temp = join_with_free(temp, var);
				free(var);
			}
			else
				temp = ft_join_char(temp, redir->file[i]);
			i++;
		}
		if (split_word_count(temp, "\x06") != 1)
		{
			if (!is_dollar && temp && !*temp)
				is_ambiguous = NOT_AMBIGUOUS;
			else
				is_ambiguous = IS_AMBIGUOUS;
		}
		else if (split_word_count(temp, "\x06") == 1)
			temp = trim_with_free(temp, "\x06");
		add_redir_node_back(new_redir, new_redir_node(temp, redir->type, is_ambiguous));
	}
	else
		add_redir_node_back(new_redir, new_redir_node(ft_strdup(redir->file), redir->type, is_ambiguous));
	return (1);
}

t_redir	*expand_redir(t_redir *redir)
{
	t_redir	*new_redir;
	t_redir	*temp;
	
	new_redir = NULL;
	temp = redir;
	while (temp)
	{
		expand_redir_string(temp, &new_redir);
		temp = temp->next;
	}
	clear_redir_list(redir);
	return (new_redir);
}
