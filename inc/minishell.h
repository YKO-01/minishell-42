/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:18:34 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 08:52:32 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include"../gnl/get_next_line.h"
# include <readline/history.h>
# include "types.h"
# include "lexer.h"
# include "parser.h"
#include "builtin_cmd.h"
#include "execution.h"
#include "expander.h"

extern t_general	general;

void	rl_replace_line(char *str, int i);

/************ prompt ***************/

char	*display_prompt(void);

/* ========== handling_input ========= */

void	check_input(char *line);
int		check_quotes(char *str);
int		check_pipes(char *str, char c);

/************ main function ********/

void	minishell(char **env);

/************ UTILS *************/

char	*trim_with_free(char *s1, char *set);
char	*join_with_free(char	*s1, char *s2);
void	free_2d_array(char **s);
void	clear_cmd(t_cmd *cmd);
t_env	*convert_env_to_list(char **env);
void	clear_lst(t_list *lst);
void	clear_env_lst(t_env *env_lst);

#endif
