/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:04:31 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/19 19:57:21 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

char	**dup_lstenv(void)
{
	char	**new_env;
	int	i;
	t_env	*tmp;

	i = 0;
	if (!g_general.env)
		return (NULL);
	new_env = malloc(sizeof(char *) * (env_list_size(g_general.env) + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	tmp = g_general.env;
	while (tmp)
	{
		new_env[i] = ft_strjoin(tmp->id, "=");
		new_env[i] = join_with_free(new_env[i], tmp->content);
		tmp = tmp->next;
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**get_new_arg(t_cmd *cmd)
{
	char **new;
	t_args *tmp;
	int	i;
	int len;
	
	i = -1;
	len = 0;
	new = malloc(sizeof(char *) * (args_list_size(cmd->args) + 1));
	if (!new)
		return (0);
	i = 0;
	tmp = cmd->args;
	while (tmp)
	{
		if (tmp->argument && tmp->argument[0] != '\0')
			new[i++] = ft_strdup(tmp->argument);
		tmp = tmp->next;
	}
	new[i] = NULL;
	return (new);
}

int	builtin_cmd(t_args *args)
{
	if (!ft_strncmp(args->argument, "cd", -1))
		return (change_dir(args->next), 0);
	if (!ft_strncmp(args->argument, "pwd", -1))
		return (ft_pwd(), 0);
	if (!ft_strncmp(args->argument, "export", -1))
		return (ft_export(args->next), 0);
	if (!ft_strncmp(args->argument, "echo", -1))
		return (ft_echo(args->next), 0);
	if (!ft_strncmp(args->argument, "env", -1))
		return (ft_env(args->next), 0);
	if (!ft_strncmp(args->argument, "unset", -1))
		return (ft_unset(args->next), 0);
	if (!ft_strncmp(args->argument, "exit", -1))
		return (ft_exit(&args), 0);
	return (1);
}

char	*ft_getenv(char *find)
{
	t_env	*tmp_env;
	
	tmp_env = g_general.env;
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->id, find, ft_strlen(find)))	
			return (tmp_env->content);
		tmp_env = tmp_env->next;
	}
	return (0);
}

int	change_value_env(char *key, char *new_value)
{
	t_env	*tmp_env;
	
	tmp_env = g_general.env;
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->id, key, ft_strlen(key)))
		{
			free(tmp_env->content);
			return (tmp_env->content = ft_strdup(new_value), 1);
		}
		tmp_env = tmp_env->next;
	}
	return (0);
}
