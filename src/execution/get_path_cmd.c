/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:02:45 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/18 13:51:45 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_path(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (env[i] && ft_strncmp(env[i], "PATH", 4) == 0)
			return (env[i] + 5);
	}
	return (NULL);
}

char	**split_path(char *path)
{
	char	**new_path;

	new_path = ft_split(path, ':');
	return (new_path);
}

char	*check_path(char *cmd, char *path)
{
	char	**new_path;
	char	*last_path;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
	}
	new_path = split_path(path);
	i = -1;
	while (new_path[++i] && *cmd)
	{
		last_path = ft_strjoin(new_path[i], "/");
		last_path = ft_strjoin(last_path, cmd);
		if (access(last_path, F_OK) == 0)
			return (free_2d_array(new_path), last_path);
		free(last_path);
	}
	ft_printf(2, "minishell: %s: command not found\n", cmd);
	return (free_2d_array(new_path), NULL);
}

char	*get_path_cmd(t_cmd *cmd, char **env)
{
	char *path_cmd;
	char	*path;
	
	path_cmd = get_path(env);
	if (!path_cmd)
	{
		if (access(cmd->args->argument, F_OK))
			return (ft_printf(2, "minishell: %s: No such file or directory\n", cmd->args->argument), NULL);
		if (access(cmd->args->argument, X_OK))
			return (ft_printf(2, "minishell: %s: Permition denied\n", cmd->args->argument), NULL);
		else
			return(cmd->args->argument);
	}
	if (ft_strchr(cmd->args->argument, '/'))
	{
		if (access(cmd->args->argument, F_OK))
			return (ft_printf(2, "minishell: %s: No such file or directory\n", cmd->args->argument), NULL);
		if (access(cmd->args->argument, X_OK))
			return (ft_printf(2, "minishell: %s: Permition denied\n", cmd->args->argument), NULL);
	}
	path = check_path(cmd->args->argument, path_cmd);
	return (path);
}