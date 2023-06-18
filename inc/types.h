/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:01:06 by osajide           #+#    #+#             */
/*   Updated: 2023/06/16 19:31:45 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef enum e_token
{
	WORD = 1,
	ENV,
	WHITE_SPACE,
	SINGLE_Q,
	DOUBLE_Q,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND_REDIR,
	HEREDOC
}	t_token;

typedef enum e_ambiguoius
{
	NOT_AMBIGUOUS = 0,
	IS_AMBIGUOUS,
	NOTHING
}	t_ambiguous ;

typedef struct s_data
{
	char	*content;
	t_token	token;
}	t_data;

typedef struct s_list
{
	t_data			*data;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_args
{
	char			*argument;
	struct s_args	*next;
}	t_args;

typedef struct s_redir
{
	char			*file;
	t_token			type;
	t_ambiguous		ambiguous;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	t_args		*args;
	t_redir		*redir;
	int			h_fd[2];
}	t_cmd;

typedef struct s_env
{
	char			*id;
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_general
{
	int	nbr_cmd;
	int	fd_in;
	int	fd_out;
	int	should_exec;
	int	exit_status;
}	t_general;

#endif