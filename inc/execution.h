/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:56:33 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/16 20:08:26 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "types.h"

void	execution_commands(t_cmd *cmd, t_env **env);
int		execute_multiple_cmd(t_cmd *cmd, t_env **env);
void	execute_cmd(t_cmd *cmd, t_env **env);
int		open_files(t_cmd cmd);


/*********** handle in out file ***************/

int handle_file_in(t_redir *redir);
int	handle_file_out(t_redir *redir);


/********* UTILS FUNCTION ************/

char	**get_new_arg(t_cmd *cmd);
char	**dup_lstenv(t_env *env);
int		builtin_cmd(t_args *args, t_env **env);
char	*ft_getenv(t_env *env, char *find);
int		change_value_env(t_env *env, char *key,char *new_value);
int		is_builtin(t_args *args);


char	*get_path_cmd(t_cmd *cmd, char **env);
void	handle_file_arg(char **args);

#endif
