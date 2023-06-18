/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 23:44:59 by osajide           #+#    #+#             */
/*   Updated: 2023/06/07 18:40:20 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_join_char(char *s, char c)
{
	char	*join;
	int		i;

	if (!s)
		s = ft_calloc(1, 1);
	join = malloc(ft_strlen(s) + 2);
	i = 0;
	while (s[i])
	{
		join[i] = s[i];
		i++;
	}
	join[i++] = c;
	join[i] = '\0';
	free(s);
	return (join);
}