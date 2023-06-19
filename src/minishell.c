/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:33:01 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/19 09:45:29 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parser.h"
#include "../inc/expander.h"
#include "../inc/execution.h"
#include <readline/history.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

t_general	general;

// void	clear_lst(t_list *lst)
// {
// 	t_list	*cur;
	
// 	if (!lst)
// 		return ;
// 	while (lst)
// 	{
// 		cur  = lst;
// 		lst = lst->next;
// 		free(cur->data->content);
// 		free(cur->data);
// 		free(cur);
// 	}
// }

void	print_linked_list(t_list *lst)
{
	t_list	*t;

	t = lst;
	while (t)
	{
		printf("\n\n\n-----------------------------\n");
		printf("t->content = %s\n", t->data->content);
		if (t->data->token == 1)
			printf("t->token = WORD\n");
		else if (t->data->token == 2)
			printf("t->token = ENV\n");
		else if (t->data->token == 3)
			printf("t->token = WHITE_SPACE\n");
		else if (t->data->token == 4)
			printf("t->token = SINGLE_Q\n");
		else if (t->data->token == 5)
			printf("t->token = DOUBLE_Q\n");
		else if (t->data->token == 6)
			printf("t->token = PIPE\n");
		else if (t->data->token == 7)
			printf("t->token = REDIR_IN\n");
		else if (t->data->token == 8)
			printf("t->token = REDIR_OUT\n");
		else if (t->data->token == 9)
			printf("t->token = APPEND_REDIR\n");
		else if (t->data->token == 10)
			printf("t->token = HEREDOC\n");
		t = t->next;
	}
}

void	handle_sigint(int sig)
{
	ft_printf(1, "\n");
	if (!general.sig_flag)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	general.exit_status = 1;
}

void	handle_signals()
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	minishell(char **env)
{
	char	*line;
	t_list	*lst;
	t_cmd	*cmd;
	t_env	*env_lst;
		general.sig_flag = 0;

	handle_signals();
	env_lst = convert_env_to_list(env);
	while (1)
	{
		general.sig_flag = 0;
		lst = NULL;
		line = display_prompt();
		if (line && line[0])
		{	
			if (check_quotes(line))
			{
				loop_on_input(line, &lst);
				if (lst)
				{
					if (!analyzer(lst))
					{
						cmd = fill_struct_cmd(lst, env_lst);
						clear_lst(lst);
						cmd = expander(cmd, env_lst);
						execution_commands(cmd, &env_lst);
						general.sig_flag = 0;
						clear_cmd(cmd);
					}
				}
			}
		}
		if (line)
			free(line);
	}
	clear_env_lst(env_lst);
}
