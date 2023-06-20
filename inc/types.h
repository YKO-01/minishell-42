/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:01:06 by osajide           #+#    #+#             */
/*   Updated: 2023/06/20 09:39:20 by ayakoubi         ###   ########.fr       */
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
}	t_ambiguous;

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

typedef struct s_g_general
{
	t_env	*env;
	int		nbr_cmd;
	int		sig_flag;
	int		exit_status;
	int		hrdc_fd;
}	t_general;

typedef struct s_fd
{
	int	fd[2];
	int	prv_fd;
}	t_fd;

#endif