/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:50:25 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/19 23:33:43 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CMD_H
# define BUILTIN_CMD_H

# include "types.h"

/************* BUILIN COMMAND ************/

void	ft_echo(t_args *args);
void	ft_pwd(void);
void	change_dir(t_args *arg);
void	ft_export(t_args *args);
void	ft_env(t_args *args);
void	ft_unset(t_args *args);
void	ft_exit(t_args **args);

/************** EXPORT UTILS ************/

char	*env_id(char *var);
char	*env_content(char *var);
void	put_new_str(char *s);

#endif