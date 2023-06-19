/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:31:51 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 17:29:33 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <limits.h>

char	*trim_with_free(char *s1, char *set)
{
	char	*str;

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
