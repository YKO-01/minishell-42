/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_env_lst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:45:34 by osajide           #+#    #+#             */
/*   Updated: 2023/06/14 17:05:38 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*add_new_env_node(char *id, char *content)
{
	t_env	*new_env_node;

	new_env_node = malloc(sizeof(t_env));
	new_env_node->id = id;
	new_env_node->content = content;
	new_env_node->next = NULL;
	new_env_node->prev = NULL;
	return (new_env_node);
}

void	add_env_node_back(t_env **env, t_env *new_env_node)
{
	t_env	*temp;

	if (! new_env_node)
		return ;
	else if (!(*env))
	{
		*env = new_env_node;
		return ;
	}
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp->next = new_env_node;
	new_env_node->next = NULL;
	new_env_node->prev = temp;
}

char	*get_env_id(char *env_var)
{
	int		i;
	int		start;
	char	*env_id;

	env_id = NULL;
	i = 0;
	start = i;
	while (env_var[i] && env_var[i] != '=')
		i++;
	env_id = ft_substr(env_var, start, i);
	return (env_id);
}

char	*get_env_content(char *env_var)
{
	char	*env_content;
	int		i;
	int		start;

	env_content = NULL;
	i = 0;
	start = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	if (env_var[i])
	{
		i++;
		start = i;
		while (env_var[i])
			i++;
	}
	env_content = ft_substr(env_var, start, i);
	return (env_content);
}

void	convert_to_env_list(char **env, t_env **env_lst)
{
	int	i;

	i = 0;
	while (env[i])
	{
		add_env_node_back(env_lst,
			add_new_env_node(get_env_id(env[i]), get_env_content(env[i])));
		i++;
	}
}
