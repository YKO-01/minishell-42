# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 11:24:45 by ayakoubi          #+#    #+#              #
#    Updated: 2023/05/29 13:31:48 by ayakoubi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
INC		=	inc

############ SRCS & DIR ##################

OBJDIR		=	obj
SRCDIR		=	src
BUILTDIR	=	builting_cmd
LEXERDIR	=	lexer
PARSERDIR	=	parser
EXECUTDIR	=	execution

SRCMAIN		=	minishell main prompt check_input check_type_cmd
BUILTSRC	:=	cd echo pwd
LEXERSRC	:=	lexer tokenize tokenize_dollar_pipe tokenize_redirection
PARSERSRC	:=	parser
EXECUTSRC	:=	

OBJ			:=	$(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCMAIN)))
SRC			:=	$(addprefix $(SRCDIR)/, $(addsuffix .c, $(SRCMAIN)))
BUILTOBJ	:=	$(addprefix $(OBJDIR)/$(BUILTDIR)/, $(addsuffix .o, $(BUILTSRC)))
BUILTSRC	:=	$(addprefix $(SRCDIR)/$(BUILTDIR)/, $(addsuffix .c, $(BUILTSRC)))
LEXEROBJ	:=	$(addprefix $(OBJDIR)/$(LEXERDIR)/, $(addsuffix .o, $(LEXERSRC)))
LEXERSRC	:=	$(addprefix $(SRCDIR)/$(LEXERDIR)/, $(addsuffix .c, $(LEXERSRC)))
PARSEROBJ	:=	$(addprefix $(OBJDIR)/$(PARSERDIR)/, $(addsuffix .o, $(PARSERSRC)))
PARSERSRC	:=	$(addprefix $(SRCDIR)/$(PARSERDIR)/, $(addsuffix .c, $(PARSERSRC)))
EXECUTOBJ	:=	$(addprefix $(OBJDIR)/$(EXECUTDIR)/, $(addsuffix .o, $(EXECUTSRC)))
EXECUTSRC	:=	$(addprefix $(SRCDIR)/$(EXECUTDIR)/, $(addsuffix .c, $(EXECUTSRC)))

############## compilation ###############

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror


C_LIBFT		=	make -C libft
C_GNL		=	make -C gnl
AR_LIBFT	=	libft/libft.a
AR_GNL		=	gnl/get_next_line

$(OBJDIR)/%.o:	$(SRCDIR)/%.c 
	@echo "compile >>>>> $^"
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(BUILTDIR)
	@mkdir -p $(OBJDIR)/$(LEXERDIR)
	@mkdir -p $(OBJDIR)/$(PARSERDIR)
	@$(CC) $(CFALGS) $< -c -I $(INC) -o $@

all:	$(NAME)

$(NAME):	$(OBJ) $(BUILTOBJ) $(LEXEROBJ) $(PARSEROBJ) $(EXECUTOBJ)
	@$(C_LIBFT) -s
	@$(C_GNL) -s
	@$(CC) $(CFLAGS) $^ $(AR_LIBFT) $(AR_GNL) -lreadline -I $(INC) -o $@

clean:
	@$(C_LIBFT) clean
	@$(C_GNL) clean
	@rm -rf *.o
	@rm -rf $(OBJDIR)
fclean: clean
	@$(C_LIBFT) fclean
	@$(C_GNL) fclean
	@rm -rf $(NAME)

re:	fclean all

.PHONY:	all clean fclean re

