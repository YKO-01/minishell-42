/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:53:55 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/12 22:14:22 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <string.h>
# include "../libft/libft.h"
# include "types.h"

t_list	*ft_lstnew(void *content, int token);
void	ft_lstadd_front(t_list **lst, t_list *new_node);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new_node);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));

/**************** lexer *****************/

void	loop_on_input(char *line, t_list **lst);
void	if_string(char *line, t_list **lst, int *pos);
char	*handle_quote(t_list **lst, char *line, int *pos, int ascii);
void	if_single_quote(char *line, t_list **lst, int *pos);
void	if_double_quote(char *line, t_list **lst, int *pos);
void	input_redirection(char *line, t_list **lst, int *pos);
void	output_redirection(char *line, t_list **lst, int *pos);
void	if_dollar_sign(char *line, t_list **lst, int *pos);
void	if_pipe(char *line, t_list **lst, int *pos);

/***************** utils **************/

int		look_for_char(char *s);
char	*ft_remove_char(char *s, int ascii);
void	skip_inside_quotes(char *line, int *pos, int ascii);

/****************** analyzer *****************/

int		analyzer(t_list *lst);

#endif
