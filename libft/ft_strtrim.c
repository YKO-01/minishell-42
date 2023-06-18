/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:18:27 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/15 16:03:00 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		begin;
	int		end;
	char	*strim;

	if (!s1 || !set)
		return (0);
	begin = 0;
	end = ft_strlen(s1);
	while (s1[begin] && check_set(s1[begin], set))
		begin++;
	while (end > begin && check_set(s1[end - 1], set))
		end--;
	strim = malloc((end - begin + 1) * sizeof(char));
	if (strim == 0)
		return (0);
	i = 0;
	while (begin < end)
	{
		strim[i] = s1[begin];
		i++;
		begin++;
	}
	strim[i] = '\0';
	return (strim);
}