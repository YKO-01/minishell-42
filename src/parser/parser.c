/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:46:28 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/05/30 13:24:32 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_cmd	*put_conten_in_cmd(t_list *lst)
// {
// 	t_cmd	*lst_cmd;
// 	//t_command	*command;
// 	t_list *count;
// 	int		i;

// 	lst_cmd->command->cmd = lst->data->content;
// 	lst = lst->next;
// 	while (lst)
// 	{
// 		while (lst && lst->data->token == 1)
// 		{
// 			count = lst;
// 			i = 0;
// 			while (count && count->data->token == 1)
// 			{
// 				i++;
// 				count = count->next;
// 			}
// 			lst_cmd->command->arg = malloc(sizeof(char *) * (i + 1));
// 			while (--i >= 0 && count && count->data->token == 1)
// 			{
// 				lst_cmd->command->arg[i] = lst->data->content;
// 				lst = lst->next;
// 			}
// 			lst_cmd->command->arg[i] = 0;
// 		}
// 		if (lst->data->token != 1)
// 			lst_cmd->
		
// 		lst = lst->next;
// 	}
// }
				
int	command_count(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		while (lst && lst->data->token != 6)
			lst = lst->next;
		if (lst)
		{
			if (lst->data->token == 6)
				count++;
			lst = lst->next;
		}
	}
	return (count + 1);
}

char	*get_command(t_list *lst, int *pos)
{
	if (lst->data->token == 1)
		return (lst->data->content);
	while (lst)
	{
		lst = lst->next;
		(*pos)++;
		while (lst && lst->data->token != 1)
		{
			lst = lst->next;
			(*pos)++;
		}
		if (lst)
		{
			lst = lst->next;
			(*pos)++;
		}
		else
			return (0);
		if (lst && lst->data->token == 1)
			break;
	}
	return (lst->data->content);
}		

char	**get_arg(t_list *lst, int *pos)
{
	int		i;
	int		len;
	t_list	*tmp;
	char	**arg;
	
	i = -1;
	while ((++i <= (*pos)) && lst)
		lst = lst->next;
	tmp = lst;
	len = 0;
	while (tmp && tmp->data->token == 1)
	{
		len++;
		tmp = tmp->next;
	}
	arg = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (lst && lst->data->token == 1)
	{
		arg[i++] = lst->data->content;
		lst = lst-> next;
	}
	arg[i] = 0;
	return (arg);
}
/*
int	get_infile(t_list *lst, int *pos)
{
	int	i;
	
} 
*/
t_command	*get_simple_command(t_list *lst, int *pos)
{
	//int	i;

	t_command *command;
	command = malloc(sizeof(t_command));
	if (!command)
		return (0);
	if (lst)
	{
		command->cmd = get_command(lst, pos);
		command->arg = get_arg(lst, pos);
	}
	return (command);
}

t_redir	*get_redir_left(t_list *lst, int pos, t_info *info)
{
	t_redir	*r_left;
	int 	i;

	if (pos == 0)
		return (0);
	info->nbr_rleft = pos / 2;
	r_left = malloc(sizeof(t_redir) * info->nbr_rleft);
	if (!r_left)
		return (0);
	i = -1;
	while (++i < info->nbr_rleft)
	{
		if (lst->data->token != 1)
		{
			r_left[i].type = lst->data->token;
			lst = lst->next;
		}
		if (lst && lst->data->token == 1)
		{
			r_left[i].arg = lst->data->content;
			lst = lst->next;
		}
	}
	return (r_left);
}

t_redir *get_redir_right(t_list *lst, int *pos, t_info *info)
{
	int i;
	t_redir *r_right;
	t_list	*tmp;

	i = -1;
	while (++i < (*pos))
		lst = lst->next;
	while (lst && lst->data->token == 1)
		lst = lst->next;
	if (!lst || lst->data->token == 6)
		return (0);
	tmp = lst;
	i = 0;
	while (tmp && tmp->data->token != 6)
	{
		tmp = tmp->next;
		i++;
	}
	info->nbr_rright = i / 2;
	r_right = malloc(sizeof(t_redir) * info->nbr_rright);
	if (!r_right)
		return (0);
	i = 0;
	while (lst && lst->data->token != 6)
	{
		if (lst && lst->data->token != 1)
		{
			r_right[i].type = lst->data->token;
			lst = lst->next;
		}
		if (lst && lst->data->token == 1)
		{
			r_right[i].arg = lst->data->content;
			lst = lst->next;
		}
		i++;
	}
	return (r_right);
}

t_cmd	*fill_struct_cmd(t_list *lst)
{
	t_cmd	*cmd;
	t_list	*tmp;
	t_info	*info;
	int	count;
	int	i;
	int pos;

	pos = 0;
	info->nbr_cmd = command_count(lst);
	info->nbr_rleft = 0;
	info->nbr_rright = 0;
	cmd = malloc(sizeof(t_cmd) * info->nbr_cmd);
	if (!cmd)
		return (0);
	tmp = lst;
	i = -1;
	while (++i < info->nbr_cmd)
	{
		cmd[i].command = get_simple_command(lst, &pos);
		cmd[i].r_left = get_redir_left(lst, pos, info);
		cmd[i].r_right = get_redir_right(lst, &pos, info);
		while (lst && lst->data->token != 6)
			lst = lst->next;
		if (lst && lst->data->token == 6)
			lst = lst->next;
		pos = 0;
	}	
	int j;
	j = -1;
	while (++j < info->nbr_cmd)
	{
		i = -1;
		while (++i < info->nbr_rleft)
		{
			printf("------------redir left----------\n");
			printf("file = %s\n", cmd[j].r_left[i].arg);
			printf("type_file = %d\n", cmd[j].r_left[i].type);
		}
		i = -1;
		while (++i < info->nbr_rright)
		{
			printf("------------redir right----------\n");
			printf("file = %s\n", cmd[j].r_right[i].arg);
			printf("type_file = %d\n", cmd[j].r_right[i].type);
		}
	}
	//printf("arg = %s\n", cmd->command->arg[0]);
	return (cmd);
}

