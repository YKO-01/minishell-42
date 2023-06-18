/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:31:51 by osajide           #+#    #+#             */
/*   Updated: 2023/06/18 23:06:31 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <limits.h>

void	clear_env_lst(t_env *env_lst)
{
	t_env	*cur;

	if (!env_lst)
		return ;
	while (env_lst)
	{
		cur = env_lst;
		env_lst = env_lst->next;
		free(cur->id);
		free(cur->content);
		free(cur);
	}
}

void	clear_lst(t_list *lst)
{
	t_list	*cur;
	
	if (!lst)
		return ;
	while (lst)
	{
		cur  = lst;
		lst = lst->next;
		free(cur->data->content);
		free(cur->data);
		free(cur);
	}
}

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
	
	if (!s1)
		s1 = ft_strdup("\0");
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
