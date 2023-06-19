/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:44:27 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 17:12:22 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

int	export_new_value(t_env *env, char *key, char *new_value)
{
	while (env)
	{
		if (!ft_strncmp(env->id, key, ft_strlen(key)))
		{
			if (!new_value)
				return (1);
			return (env->content = new_value, 1);
		}
		env = env->next;
	}
	return (0);
}

char	*env_id(char *var)
{
	int		i;
	int		start;
	char	*env_id;

	i = 0;
	env_id = NULL;
	start = i;
	while (var[i] && var[i] != '=')
		i++;
	env_id = ft_substr(var, start, i);
	return (env_id);
}

char	*env_content(char *var)
{
	int		i;
	int		start;
	int		check_if_value;
	char	*env_content;

	i = 0;
	env_content = NULL;
	start = i;
	while (var[i] && var[i] != '=')
		i++;
	check_if_value = i;
	if (var[i] == '=')
		i++;
	if (i - check_if_value > 0)
		env_content = ft_substr(var, i, ft_strlen(var));
	return (env_content);
}

void	put_new_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '$')
			printf("\\");
		printf("%c", s[i]);
		i++;
	}
}

int	check_var_identifier(char *s)
{
	int	i;

	i = 1;
	if (!((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z') || (s[0] == '_')))
		return (0);
	else
	{
		while (s[i])
		{
			if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_') || (s[i] >= '0' && s[i] <= '9')))
				return (0);
			i++;
		}
	}
	return (1);
}

void	ft_export(t_args *args, t_env *env_lst)
{
	t_env	*temp;
	char	*ptr;

	temp = env_lst;
	if (!args)
	{
		while (temp)
		{
			printf("declare -x %s", temp->id);
			if (temp->content)
			{
				printf("=\"");
				put_new_str(temp->content);
				printf("\"\n");
			}
			else
				printf("\n");
			temp = temp->next;
		}	
	}
	else
	{
		while (args)
		{
			char *id = env_id(args->argument);
			if (check_var_identifier(id))
			{
				char *content = env_content(args->argument);
				if (!export_new_value(env_lst, id,  content))
				{
					ptr = ft_strchr(args->argument, '=');
					if (!ptr)
						add_env_node_back(&env_lst, add_new_env_node(id, NULL));
					else
					{
						if (!ft_strncmp(ptr, "=", ft_strlen(ptr)))
							add_env_node_back(&env_lst, add_new_env_node(id, ""));
						else
							add_env_node_back(&env_lst, add_new_env_node(id, content));
					}
				}
			}
			else
			{
				g_general.exit_status = 1;
				ft_printf(2, "minishell: export: '%s': not a valid identifier\n", args->argument);
			}
			args = args->next;
		}
	}
}