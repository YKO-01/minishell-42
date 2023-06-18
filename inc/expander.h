/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:51:02 by osajide           #+#    #+#             */
/*   Updated: 2023/06/13 22:09:18 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <stdlib.h>
#include "types.h"

t_cmd	*expander(t_cmd *cmd, t_env *env_lst);

/****************** split_charset and utils ***************/

int		split_word_count(char const *s, char *charset);
char	**ft_split_charset(char const *s, char *charset);
int		if_should_split(char *var);
void	replace_var_in_args_list(char *before_var, char *var, t_args **new_args);

/************** env linked list *************/

t_env	*add_new_env_node(char *id, char *content);
void	add_env_node_back(t_env **env, t_env *new_env_node);
char	*get_env_id(char *env_var);
char	*get_env_content(char *env_var);
void	convert_to_env_list(char **env, t_env **env_lst);

/*************** expander **************/

char	*handle_dollar_sign(char *s, int *pos, t_env *env_lst);
char	*handle_dollar_sign_inside_d_quotes(char *s, int *pos, t_env *env_lst);
char	*expand_inside_single_quotes(char *s, int *pos);
char	*expand_inside_double_quotes(char *s, int *pos, t_env *env_lst);

void	expand_args_string(char *s, t_env *env_lst, t_args **args);
void	clear_args_list(t_args *args);
void	clear_redir_list(t_redir *redir);

t_args	*expand_args(t_args *args, t_env *env_lst);
int		expand_cmd(t_cmd *cmd, t_env *env_lst);
char	*handle_dollar_sign_inside_d_quotes(char *s, int *pos, t_env *env_lst);

/*************** expand quotes **************/

char	*expand_inside_single_quotes(char *s, int *pos);
char	*expand_inside_double_quotes(char *s, int *pos, t_env *env_lst);

/**************** expand redirection ********************/

t_redir	*expand_redir(t_redir *redir, t_env *env_lst);

/**************  args_expansion ***************/

void	expand_args_string(char *s, t_env *env_lst, t_args **args);
t_args	*expand_args(t_args *args, t_env *env_lst);

#endif