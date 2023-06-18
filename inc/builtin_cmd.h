/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:50:25 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/18 23:13:40 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CMD_H
# define BUILTIN_CMD_H

# include "types.h"

/************* BUILIN COMMAND ************/

void	ft_echo(t_args *args);
void	ft_pwd(void);
void	change_dir(t_args *arg, t_env *env);
void	ft_export(t_args *args, t_env *env_lst);
void	ft_env(t_env *env, t_args *args);
void	ft_unset(t_args *args, t_env **env_lst);
void	ft_exit(t_args **args, t_env **env_lst);

/************** BUILTIN UTILS ************/

#endif