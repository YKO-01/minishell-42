/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:44:27 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 23:34:39 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

int	export_new_value(char *key, char *new_value)
{
	t_env	*tmp_env;

	tmp_env = g_general.env;
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->id, key, ft_strlen(key)))
		{
			if (!new_value)
				return (1);
			return (free(tmp_env->content), tmp_env->content = new_value, 1);
		}
		tmp_env = tmp_env->next;
	}
	return (0);
}

int	check_var_identifier(char *s)
{
	int	i;

	i = 1;
	if (!((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z')
			|| (s[0] == '_')))
		return (0);
	else
	{
		while (s[i])
		{
			if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
					|| (s[i] == '_') || (s[i] >= '0' && s[i] <= '9')))
				return (0);
			i++;
		}
	}
	return (1);
}

void	print_export(t_env *env)
{
	while (env)
	{
		printf("declare -x %s", env->id);
		if (env->content)
		{
			printf("=\"");
			put_new_str(env->content);
			printf("\"\n");
		}
		else
			printf("\n");
		env = env->next;
	}	
}

void	check_and_add_var(t_env *env, t_args *args, char *id)
{
	char	*ptr;
	char	*content;

	content = env_content(args->argument);
	if (!export_new_value(id, content))
	{
		ptr = ft_strchr(args->argument, '=');
		if (!ptr)
			add_env_node_back(&g_general.env,
				add_new_env_node(ft_strdup(id), NULL));
		else
		{
			if (!ft_strncmp(ptr, "=", ft_strlen(ptr)))
				add_env_node_back(&g_general.env,
					add_new_env_node(ft_strdup(id), ""));
			else
				add_env_node_back(&g_general.env,
					add_new_env_node(ft_strdup(id), content));
		}
	}
}

void	ft_export(t_args *args)
{
	t_env	*tmp_env;
	char	*id;

	tmp_env = g_general.env;
	if (!args)
		print_export(g_general.env);
	else
	{
		while (args)
		{
			id = env_id(args->argument);
			if (check_var_identifier(id))
				check_and_add_var(g_general.env, args, id);
			else
			{
				g_general.exit_status = 1;
				ft_printf(2, "minishell: export: '%s': not a valid identifier\n",
					args->argument);
			}
			free(id);
			args = args->next;
		}
	}
}
