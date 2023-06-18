/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:11:53 by osajide           #+#    #+#             */
/*   Updated: 2023/06/14 21:19:13 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include <stdio.h>

t_redir	*new_redir_node(char *file, int type, int ambiguous)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (0);
	redir->file = file;
	redir->type = type;
	redir->ambiguous = ambiguous;
	redir->next = NULL;
	return (redir);
}

void	add_redir_node_back(t_redir **redir, t_redir *new_node)
{
	t_redir	*tmp;

	if (!new_node)
		return ;
	if (!*redir)
	{
		*redir = new_node;
		return ;
	}
	tmp = *redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

t_args	*new_args_node(char	*content)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (0);
	args->argument = content;
	args->next = NULL;
	return (args);
}

void	add_args_node_back(t_args **args, t_args *node)
{
	t_args	*tmp;

	if (!node)
		return ;
	if (!*args)
	{
		*args = node;
		return ;
	}
	tmp = *args;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}
