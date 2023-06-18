/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:04:31 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/17 16:14:49 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

char	**dup_lstenv(t_env *env)
{
	char	**new_env;
	int	i;
	t_env	*tmp;

	i = 0;
	if (!env)
		return (0);
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (0);
	i = -1;
	tmp = env;
	while (tmp)
	{
		new_env[i] = ft_strjoin(tmp->id, "=");
		new_env[i] = ft_strjoin(new_env[i], tmp->content);
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
	tmp = cmd->args;
	while (tmp)
	{
		if (tmp->argument)
			len++;
		tmp = tmp->next;
	}
	new = malloc(sizeof(char *) * (len + 1));
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

int	builtin_cmd(t_args *args, t_env **env)
{
	if (!ft_strncmp(args->argument, "cd", -1))
		return (change_dir(args->next, *env), 0);
	if (!ft_strncmp(args->argument, "pwd", -1))
		return (ft_pwd(), 0);
	if (!ft_strncmp(args->argument, "export", -1))
		return (ft_export(args->next ,*env), 0);
	if (!ft_strncmp(args->argument, "echo", -1))
		return (ft_echo(args->next), 0);
	if (!ft_strncmp(args->argument, "env", -1))
		return (ft_env(*env, args->next), 0);
	if (!ft_strncmp(args->argument, "unset", -1))
		return (ft_unset(args->next, env), 0);
	if (!ft_strncmp(args->argument, "exit", -1))
		return (ft_exit(&args, env), 0);
	return (1);
}

char	*ft_getenv(t_env *env, char *find)
{
	while (env)
	{
		if (!ft_strncmp(env->id, find, ft_strlen(find)))	
			return (env->content);
		env = env->next;
	}
	return (0);
}

int	change_value_env(t_env *env, char *key, char *new_value)
{
	while (env)
	{
		if (!ft_strncmp(env->id, key, ft_strlen(key)))
			return (env->content = new_value, 1);
		env = env->next;
	}
	return (0);
}
