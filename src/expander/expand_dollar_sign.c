/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:33:29 by osajide           #+#    #+#             */
/*   Updated: 2023/06/16 22:11:36 by osajide          ###   ########.fr       */
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

char	*handle_dollar_sign(char *s, int *pos, t_env *env_lst)
{
	char	*temp;
	int		start;
	int		i;

	i = *pos;
	temp = NULL;
	(*pos)++;
	skip_dollars(s, pos);
	if (!s[*pos])
		return ((*pos)-- , ft_join_char(temp, '$'));
	else if (s[*pos] == '?')
		return (ft_itoa(general.exit_status));
	else if (s[*pos] == '\'' || s[*pos] == '"')
		return ((*pos)--, ft_join_char(temp, '\0'));
	if (!(ft_isalpha(s[*pos]) || s[*pos] == '_'))
	{
		(*pos)++;
		start = *pos;
		while (s[*pos])
			(*pos)++;
		temp = ft_substr(s, start, *pos);
	}
	else
	{
		start = *pos;
		while (ft_isalnum(s[*pos]) || s[*pos] == '_')
			(*pos)++;
		temp = ft_substr(s, start, *pos);
		while (env_lst)
		{
			if (!ft_strncmp(temp, env_lst->id, ft_strlen(temp)))
				return ((*pos)--, env_lst->content);
			env_lst = env_lst->next;
		}
		if (!env_lst)
		{
			ft_bzero(temp, ft_strlen(temp));
			return ((*pos)--, temp);
		}
	}
	return ((*pos)--, temp);
}

char	*handle_dollar_sign_inside_d_quotes(char *s, int *pos, t_env *env_lst)
{
	char	*temp;
	int		start;

	temp = NULL;
	(*pos)++;
	if (s[*pos] == '?')
		return (ft_itoa(general.exit_status));
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
	{
		start = *pos;
		while (ft_isalnum(s[*pos]) || s[*pos] == '_')
			(*pos)++;
		temp = ft_substr(s, start, *pos);
		while (env_lst)
		{
			if (!ft_strncmp(temp, env_lst->id, ft_strlen(temp)))
				return (env_lst->content);
			env_lst = env_lst->next;
		}
		if (!env_lst)
		{
			ft_bzero(temp, ft_strlen(temp));
			return (temp);
		}
	}
	return (temp);
}
