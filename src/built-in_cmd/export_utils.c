/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:32:50 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 23:33:09 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
