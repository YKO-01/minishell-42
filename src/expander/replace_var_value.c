/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 20:52:39 by osajide           #+#    #+#             */
/*   Updated: 2023/06/18 12:25:23 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	if_should_split(char *var)
{
	int	i;
	
	if (split_word_count(var, "\t ") == 0)
		return (0);
	i = 0;
	while (var[i])
	{
		if (var[i] == '\t' || var[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}
 
void	replace_var_in_args_list(char *before_var, char *var, t_args **new_args)
{
	int		i;
	char	*temp;
	char	**split;

	i = 0;
	temp = before_var;
	split = ft_split_charset(var, "\t ");
	while (split && split[i])
	{
		add_args_node_back(new_args, new_args_node(ft_strjoin(before_var, ft_strdup(split[i]))));
		before_var = NULL;
		i++;
	}
	free_2d_array(split);
}

