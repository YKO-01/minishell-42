/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:33:29 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 22:35:14 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

void	skip_dollars(char *s, int *pos)
{
	int	check;

	check = 0;
	while (s[*pos] == '$')
	{	
		check++;
		(*pos)++;
	}
	if (check > 0 && check % 2 != 0)
		(*pos)--;
}

char	*give_expanded_value(char *s, int *pos)
{
	int		start;
	char	*temp;
	t_env	*tmp_env;

	start = *pos;
	temp = NULL;
	tmp_env = g_general.env;
	while (ft_isalnum(s[*pos]) || s[*pos] == '_')
		(*pos)++;
	temp = ft_substr(s, start, *pos);
	while (tmp_env)
	{
		if (!ft_strncmp(temp, tmp_env->id, ft_strlen(temp)))
			return (free(temp), ft_strdup(tmp_env->content));
		tmp_env = tmp_env->next;
	}
	if (!tmp_env)
	{
		ft_bzero(temp, ft_strlen(temp));
		return (temp);
	}
	return (temp);
}

char	*if_not_a_valid_identifier(char *s, int *pos)
{
	int		start;
	char	*temp;

	temp = NULL;
	(*pos)++;
	start = *pos;
	while (s[*pos])
		(*pos)++;
	temp = ft_substr(s, start, *pos);
	return (temp);
}

char	*handle_dollar_sign(char *s, int *pos)
{
	char	*temp;
	int		start;
	int		i;
	t_env	*tmp_env;

	tmp_env = g_general.env;
	i = *pos;
	temp = NULL;
	(*pos)++;
	skip_dollars(s, pos);
	if (!s[*pos])
		return ((*pos)--, ft_join_char(temp, '$'));
	else if (s[*pos] == '?')
		return (ft_itoa(g_general.exit_status));
	else if (s[*pos] == '\'' || s[*pos] == '"')
		return ((*pos)--, ft_join_char(temp, '\0'));
	if (!(ft_isalpha(s[*pos]) || s[*pos] == '_'))
		temp = if_not_a_valid_identifier(s, pos);
	else
		temp = give_expanded_value(s, pos);
	return ((*pos)--, temp);
}

char	*handle_dollar_sign_inside_d_quotes(char *s, int *pos, t_env *env_lst)
{
	char	*temp;
	int		start;

	temp = NULL;
	(*pos)++;
	if (s[*pos] == '?')
		return (ft_itoa(g_general.exit_status));
	if (s[*pos] == ' ')
	{
		start = *pos - 1;
		while (s[*pos] != 34)
			(*pos)++;
		temp = ft_substr(s, start, *pos);
	}
	else if (!(ft_isalpha(s[*pos]) || s[*pos] == '_'))
	{
		(*pos)++;
		start = *pos;
		while (s[*pos] != 34)
			(*pos)++;
		temp = ft_substr(s, start, *pos);
	}
	else
		temp = give_expanded_value(s, pos);
	return (temp);
}
