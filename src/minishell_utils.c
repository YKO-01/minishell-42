/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:31:51 by osajide           #+#    #+#             */
/*   Updated: 2023/06/18 13:22:39 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*join_with_free(char *s1, char *s2)
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


t_env	*convert_env_to_list(char **env)
{
	int	i;
	t_env *env_lst;
	env_lst = NULL;
	i = 0;
	while (env[i])
	{
		add_env_node_back(&env_lst,
			add_new_env_node(get_env_id(env[i]), get_env_content(env[i])));
		i++;
	}
	return (env_lst);
}