/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:51:02 by osajide           #+#    #+#             */
/*   Updated: 2023/06/19 22:09:54 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "types.h"

t_cmd	*expander(t_cmd *cmd);

/****************** split_charset and utils ***************/

int		split_word_count(char const *s, char *charset);
char	**ft_split_charset(char const *s, char *charset);
int		if_should_split(char *var);
void	replace_var_in_args_list(char *before_var, char *var,
			t_args **new_args);
char	*replace_spaces(char *var);

/************** env linked list *************/

t_env	*add_new_env_node(char *id, char *content);
void	add_env_node_back(t_env **head, t_env *new_env_node);
char	*get_env_id(char *env_var);
char	*get_env_content(char *env_var);
void	convert_to_env_list(char **env, t_env **env_lst);

/*************** expander **************/

char	*handle_dollar_sign(char *s, int *pos);
char	*handle_dollar_sign_inside_d_quotes(char *s, int *pos, t_env *env_lst);

void	clear_args_list(t_args *args);
void	clear_redir_list(t_redir *redir);

int		expand_cmd(t_cmd *cmd);
char	*handle_dollar_sign_inside_d_quotes(char *s, int *pos, t_env *env_lst);

/*************** expand quotes **************/

char	*expand_inside_single_quotes(char *s, int *pos);
char	*expand_inside_double_quotes(char *s, int *pos);

/**************** expand redirection ********************/

t_redir	*expand_redir(t_redir *redir);
int		expand_redir_string(t_redir *redir, t_redir **new_redir);

/**************  args_expansion ***************/

void	expand_args_string(char *s, t_args **args);
t_args	*expand_args(t_args *args);

#endif