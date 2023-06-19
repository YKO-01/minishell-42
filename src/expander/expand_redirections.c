/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:26:45 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 22:10:13 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*quote_cases(char *file, int *pos, char *before)
{
	char	*temp;

	temp = NULL;
	if (file[*pos] == 39)
	{
		temp = expand_inside_single_quotes(file, pos);
		before = join_with_free(before, temp);
		free(temp);
	}
	else if (file[*pos] == 34)
	{
		temp = expand_inside_double_quotes(file, pos);
		before = join_with_free(before, temp);
		free(temp);
	}
	return (before);
}

char	*redir_dollar_sign_case(char *file, int *pos,
	char *before, int *is_dollar)
{
	char	*var;

	var = NULL;
	var = handle_dollar_sign(file, pos);
	if (!before && !var[0])
		*is_dollar = 1;
	var = replace_spaces(var);
	before = join_with_free(before, var);
	free(var);
	return (before);
}

void	check_ambiguous(char **before, int *is_dollar, int *is_ambiguous)
{
	if (split_word_count(*before, "\x06") != 1)
	{
		if (!*is_dollar && *before && !**before)
			*is_ambiguous = NOT_AMBIGUOUS;
		else
			*is_ambiguous = IS_AMBIGUOUS;
	}
	else if (split_word_count(*before, "\x06") == 1)
		*before = trim_with_free(*before, "\x06");
}

char	*loop_on_redir_file(char *file, int *pos, char *before, int *is_dollar)
{
	if (file[*pos] == 39 || file[*pos] == 34)
		before = quote_cases(file, pos, before);
	else if (file[*pos] == '$')
		before = redir_dollar_sign_case(file, pos, before, is_dollar);
	else
		before = ft_join_char(before, file[*pos]);
	return (before);
}

int	expand_redir_string(t_redir *redir, t_redir **new_redir)
{
	int		i;
	char	*temp;
	int		is_dollar;
	int		is_ambiguous;

	i = 0;
	is_ambiguous = NOTHING;
	temp = NULL;
	if (redir->type != HEREDOC)
	{
		while (redir->file[i])
		{
			is_dollar = 0;
			temp = loop_on_redir_file(redir->file, &i, temp, &is_dollar);
			i++;
		}
		check_ambiguous(&temp, &is_dollar, &is_ambiguous);
		add_redir_node_back(new_redir,
			new_redir_node(temp, redir->type, is_ambiguous));
	}
	else
		add_redir_node_back(new_redir,
			new_redir_node(ft_strdup(redir->file),
				redir->type, is_ambiguous));
	return (1);
}
