/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:07:03 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/05/21 17:04:46 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*newstr;

	size = len + 1;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		newstr = malloc(1);
		newstr[0] = 0;
		return (newstr);
	}
	i = 0;
	j = start;
	newstr = malloc(size);
	if (!newstr)
		return (NULL);
	while (j < len)
		newstr[i++] = s[j++];
	newstr[i] = '\0';
	return (newstr);
}

