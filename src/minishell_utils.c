/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:31:51 by osajide           #+#    #+#             */
/*   Updated: 2023/06/18 18:41:16 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*trim_with_free(char *s1, char *set)
{
	char *str;

	str = ft_strtrim(s1, set);
	free(s1);
	return (str);
}

char	*join_with_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (tmp);
}

void	free_2d_array(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	clear_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < general.nbr_cmd)
	{
		clear_args_list(cmd[i].args);
		clear_redir_list(cmd[i].redir);
	}
	free(cmd);
}
