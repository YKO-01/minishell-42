/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:33:01 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/20 11:22:49 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_sigint(int sig)
{
	ft_printf(1, "\n");
	if (g_general.hrdc_fd >= 0)
	{
		close(g_general.hrdc_fd);
		g_general.hrdc_fd = -2;
		g_general.exit_status = 130;
		return ;
	}
	else if (!g_general.sig_flag)
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
					if (g_general.hrdc_fd != -2)
					{
						cmd = expander(cmd);
						execution_commands(cmd);
						clear_cmd(cmd);
					}
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
		g_general.hrdc_fd = -1;
		g_general.sig_flag = 0;
		*lst = NULL;
		line = display_prompt();
		loop_on_input(line, lst);
		if (line)
			free(line);
	}
}
