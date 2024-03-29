/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:54:22 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/05/21 19:25:22 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

t_list	*ft_lstnew(void *content, int state, int token)
{
	t_list	*node;
	t_data	*data;
	node = malloc(sizeof(t_list));
	data = malloc(sizeof(t_data));
	if (!node)
		return (0);
	data->content = content;
	data->state = state;
	data->token = token,
	node->data = data;
	node->next = NULL;
	return (node);
}
