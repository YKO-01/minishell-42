/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:26:45 by osajide           #+#    #+#             */
/*   Updated: 2023/06/16 19:41:55 by osajide          ###   ########.fr       */
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

int	expand_redir_string(t_redir *redir, t_env *env_lst, t_redir **new_redir)
{
	int		i;
	char	*temp;
	char	*var;
	char	*ambiguous;
	int		is_dollar;
	int		is_ambiguous;

	i = 0;
	ambiguous = redir->file;
	is_ambiguous = NOTHING;
	temp = NULL;
	var = NULL;
	if (redir->type != HEREDOC)
	{
		while (redir->file[i])
		{
			is_dollar = 0;
			if (redir->file[i] == 39)
				temp =  ft_strjoin(temp, expand_inside_single_quotes(redir->file, &i));
			else if (redir->file[i] == 34)
				temp = ft_strjoin(temp, expand_inside_double_quotes(redir->file, &i, env_lst));
			else if (redir->file[i] == '$')
			{
				var = handle_dollar_sign(redir->file, &i, env_lst);
				if (!temp && !var[0])
					is_dollar = 1;
				var = replace_spaces(var);
				temp = ft_strjoin(temp, var);
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
			temp = ft_strtrim(temp, "\x06");
		add_redir_node_back(new_redir, new_redir_node(temp, redir->type, is_ambiguous));
	}
	else
		add_redir_node_back(new_redir, new_redir_node(redir->file, redir->type, is_ambiguous));
	return (1);
}

t_redir	*expand_redir(t_redir *redir, t_env *env_lst)
{
	t_redir	*new_redir;
	
	new_redir = NULL;
	while (redir)
	{
		expand_redir_string(redir, env_lst, &new_redir);
		redir = redir->next;
	}
	clear_redir_list(redir);
	return (new_redir);
}
