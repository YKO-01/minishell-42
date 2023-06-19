/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:33:01 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/19 19:45:23 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_sigint(int sig)
{
	ft_printf(1, "\n");
	if (!g_general.sig_flag)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_general.exit_status = 1;
}

void	handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	loop_on_input(char *line, t_list **lst)
{
	t_cmd	*cmd;

	if (line && line[0])
	{	
		if (check_quotes(line))
		{
			lexer(line, lst);
			if (lst)
			{
				if (!analyzer(*lst))
				{
					cmd = fill_struct_cmd(*lst);
					clear_lst(*lst);
					cmd = expander(cmd);
					execution_commands(cmd);
					clear_cmd(cmd);
				}
			}
		}
	}
}

void	minishell(t_list **lst)
{
	char	*line;

	while (1)
	{
		g_general.sig_flag = 0;
		*lst = NULL;
		line = display_prompt();
		loop_on_input(line, lst);
		if (line)
			free(line);
	}
}
