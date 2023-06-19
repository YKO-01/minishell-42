/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:56:33 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/19 23:54:27 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "types.h"

void	execution_commands(t_cmd *cmd);
int		execute_multiple_cmd(t_cmd *cmd);
int     loop_execute_cmd(t_cmd *cmd, int *pid);
void	close_file_parent(t_cmd *cmd, t_fd *file_d, int i);
void	exec_child_pro(t_cmd *cmd, t_fd *file_d, int i);
void	execute_cmd(t_cmd *cmd);

/*********** FILES ***************/

int		open_files(t_cmd cmd);
int     open_file_in(t_redir *redir);
int     open_file_out_and_append(t_redir *redir);
int		handle_file_in(t_redir *redir);
int		handle_file_out(t_redir *redir);

/********* UTILS FUNCTION ************/

char	**get_new_arg(t_cmd *cmd);
char	**dup_lstenv(void);
int		builtin_cmd(t_args *args);
char	*ft_getenv(char *find);
int		change_value_env(char *key, char *new_value);
int		is_builtin(t_args *args);

char	*get_path_cmd(t_cmd *cmd, char **env);
int		env_list_size(t_env *env);
int		args_list_size(t_args *args);

#endif