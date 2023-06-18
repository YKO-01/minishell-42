/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:46:28 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/18 22:50:23 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

int	command_number(t_list *lst)
{
	int	command_counter;

	command_counter = 1;
	while (lst)
	{
		if (lst->data->token == PIPE)
			command_counter++;
		lst = lst->next;
	}
	return (command_counter);
}

char	*get_command(t_list *lst, int *pos)
{
	while (lst && lst->data->token != PIPE)
	{
		if (lst->data->token != WORD && lst->data->token != ENV)
		{
			lst = lst->next->next;
			(*pos)++;
			(*pos)++;
		}
		if (lst && (lst->data->token == WORD || lst->data->token == ENV))
			return (ft_strdup(lst->data->content));
	}
	return (NULL);
} 

t_args	*get_arg(t_list *lst, int *pos)
{
	t_args	*args;
	int		i;

	args = NULL;
	add_args_node_back(&args, new_args_node(get_command(lst, pos)));
	i = -1;
	while ((++i <= (*pos)) && lst)
		lst = lst->next;
	while (lst && lst->data->token != PIPE)
	{
		if (lst->data->token != WORD && lst->data->token != ENV)
		{
			lst = lst->next;
			if (lst)
				lst = lst->next;
		}
		while (lst && (lst->data->token == WORD || lst->data->token == ENV))
		{
			add_args_node_back(&args, new_args_node(ft_strdup(lst->data->content)));
			lst = lst->next;
		}
	}
	return (args);
}

t_redir	*fill_struct_redir(t_list *lst)
{
	t_redir	*redir;

	redir = NULL;
	while (lst && lst->data->token != PIPE)
	{
		if (lst->data->token != WORD && lst->data->token != ENV)
		{
			lst = lst->next;
			if (lst && (lst->data->token == WORD || lst->data->token == ENV))
				add_redir_node_back(&redir,
					new_redir_node(ft_strdup(lst->data->content), lst->prev->data->token, NOTHING));
		}
		lst = lst->next;
	}
	return (redir);
}

void	print_parser(t_cmd *cmd, int count_cmd)
{
	int		i;
	int		j;
	t_args	*tmp_args;
	t_redir	*tmp_redir;

	i = -1;
	tmp_redir = cmd->redir;
	while (++i < count_cmd)
	{
		tmp_args = cmd[i].args;
		if (tmp_args)
		{
			printf("\n******** COMMAND [%d]**************\n\n", i + 1);
			while (tmp_args)
			{
				printf("\t\033[1;32margument =\033[0m %s\n", tmp_args->argument);
				tmp_args = tmp_args->next;
			}
		}
		if (tmp_redir)
		{
			printf("\n******** REDIRECTION [%d]**************\n\n", i + 1);
			while (tmp_redir)
			{
				printf("\tfile == %s\n", tmp_redir->file);
				if (tmp_redir->type == REDIR_IN)
					printf("\ttype == %s\n", "REDIR_IN\n");
				else if (tmp_redir->type == REDIR_OUT)
					printf("\ttype == %s\n", "REDIR_OUT\n");
				else if (tmp_redir->type == HEREDOC)
					printf("\ttype == %s\n", "HEREDOC\n");
				else if (tmp_redir->type == APPEND_REDIR)
					printf("\ttype == %s\n", "APPEND_REDIR\n");
				tmp_redir = tmp_redir->next;
			}
		}
	}
}

t_cmd	*fill_struct_cmd(t_list *lst, t_env *env_lst)
{
	t_cmd	*cmd;
	int		i;
	int		pos;
	
	general.nbr_cmd = command_number(lst);
	cmd = malloc(general.nbr_cmd * sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	pos = 0;
	i = 0;
	while (i < general.nbr_cmd)
	{
		cmd[i].args = get_arg(lst, &pos);
		cmd[i].redir = fill_struct_redir(lst);
		cmd[i].h_fd[0] = -1;
		cmd[i].h_fd[1] = -1;
		read_herdoc(&cmd[i], env_lst);
		i++;
		while (lst && lst->data->token != PIPE)
			lst = lst->next;
		if (lst && lst->data->token == PIPE)
			lst = lst->next;
		pos = 0;
	}
	// print_parser(cmd, general.nbr_cmd);
	return (cmd);
}
