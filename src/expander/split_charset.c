/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_charset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:36:47 by osajide           #+#    #+#             */
/*   Updated: 2023/06/13 18:34:14 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	split_word_count(char const *s, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (in_charset(s[i], charset))
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && !in_charset(s[i], charset))
			i++;
	}
	return (count);
}

int	w_len(char const *s, char *charset)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (in_charset(s[i], charset))
		i++;
	while (s[i] && !in_charset(s[i], charset))
	{
		len++;
		i++;
	}
	return (len);
}

char	*w_fil(char const *s, char *charset)
{
	int		i;
	int		j;
	char	*w;

	i = 0;
	j = 0;
	w = ft_calloc(w_len(s, charset) + 1, sizeof(char));
	while (in_charset(s[i], charset))
		i++;
	if (s[i] && !in_charset(s[i], charset))
		ft_memcpy(w, s, w_len(s, charset));
	return (w);
}

char	**ft_split_charset(char const *s, char *charset)
{
	int		i;
	int		j;
	char	**split;

	if (!s)
		return (0);
	i = 0;
	j = split_word_count(s, charset);
	split = malloc((j + 1) * sizeof(char *));
	if (!split)
		return (0);
	while (*s && j)
	{
		while (in_charset(*s, charset))
			s++;
		split[i] = w_fil(s, charset);
		s = s + w_len(s, charset);
		while (*s && in_charset(*s, charset))
			s++;
		i++;
	}
	split[i] = NULL;
	return (split);
}
