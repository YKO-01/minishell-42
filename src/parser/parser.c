/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:46:28 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/05/29 18:15:27 by ayakoubi         ###   ########.fr       */
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
	printf("lst content : %s\n", lst->data->content);
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
t_command	*get_simple_command(t_list *lst)
{
	//int	i;
	int pos;
	
	pos = 0;
	t_command *command;
	command = malloc(sizeof(t_command));
	if (!command)
		return (0);
	if (lst)
	{
		command->cmd = get_command(lst, &pos);
		command->arg = get_arg(lst, &pos);
	}
	printf("pos = %d\n", pos);
	printf("arg = %s\n", command->arg[0]);
	return (command);
}

t_cmd	*fill_struct_cmd(t_list *lst)
{
	t_cmd	*cmd;
	int	count;

	count = command_count(lst);
	printf("nbr command %d\n", count);
	cmd = malloc(sizeof(t_cmd) * count);
	if (!cmd)
		return (0);
	cmd->command = get_simple_command(lst);
	printf("cmd = %s\n", cmd->command->cmd);
	//printf("arg = %s\n", cmd->command->arg[0]);
	return (cmd);
}

