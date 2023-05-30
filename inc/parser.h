/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:59:07 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/05/30 11:45:18 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"


/********* DEFINES *************/

# define nbr_cmd int
# define nbr_rleft int
# define nbr_rright int


typedef struct s_command
{
	char *cmd;
	char **arg;
	// int	infile;
	// int	outfile;
}	t_command;

typedef struct s_redir
{
	char	*arg;
	int	type;
}	t_redir;

typedef struct s_cmd
{
	t_command	*command;
	t_redir	*r_left;
	t_redir *r_right;
	int		infile;
	int		outfile;
}	t_cmd;

t_cmd	*fill_struct_cmd(t_list *lst);

/************ PARSER UTILS ***********/



#endif

