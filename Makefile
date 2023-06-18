# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 11:24:45 by ayakoubi          #+#    #+#              #
#    Updated: 2023/06/18 14:04:16 by ayakoubi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
INC		=	inc

############ Colors ######################

RED = \033[1;31m
GREEN = \033[1;32m
SPLASH = \033[5m
BLUE = \033[1;34m
YELLOW = \033[1;33m
RESET = \033[0m

############ SRCS & DIR ##################

OBJDIR		=	obj
SRCDIR		=	src
BUILTDIR	=	built-in_cmd
LEXERDIR	=	lexer
PARSERDIR	=	parser
EXPANDERDIR	=	expander
EXECUTDIR	=	execution

SRCMAIN		=	minishell main prompt check_quotes minishell_utils
BUILTSRC	:=	cd echo pwd export env unset exit
LEXERSRC	:=	lexer tokenize tokenize_dollar_pipe tokenize_redirection analyzer \
				utils
PARSERSRC	:=	parser parser_utils heredoc
EXPANDERSRC	:=	expander convert_to_env_lst expand_dollar_sign expand_cmd \
				expand_inside_quotes replace_var_value split_charset clear_lists \
				args_expansion
EXECUTSRC	:=	get_path_cmd execute_cmd execution_utils execute_multiple_cmd \
				handle_file builtin_utils

OBJ			:=	$(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCMAIN)))
SRC			:=	$(addprefix $(SRCDIR)/, $(addsuffix .c, $(SRCMAIN)))
BUILTOBJ	:=	$(addprefix $(OBJDIR)/$(BUILTDIR)/, $(addsuffix .o, $(BUILTSRC)))
BUILTSRC	:=	$(addprefix $(SRCDIR)/$(BUILTDIR)/, $(addsuffix .c, $(BUILTSRC)))
LEXEROBJ	:=	$(addprefix $(OBJDIR)/$(LEXERDIR)/, $(addsuffix .o, $(LEXERSRC)))
LEXERSRC	:=	$(addprefix $(SRCDIR)/$(LEXERDIR)/, $(addsuffix .c, $(LEXERSRC)))
PARSEROBJ	:=	$(addprefix $(OBJDIR)/$(PARSERDIR)/, $(addsuffix .o, $(PARSERSRC)))
PARSERSRC	:=	$(addprefix $(SRCDIR)/$(PARSERDIR)/, $(addsuffix .c, $(PARSERSRC)))
EXPANDEROBJ	:=	$(addprefix $(OBJDIR)/$(EXPANDERDIR)/, $(addsuffix .o, $(EXPANDERSRC)))
EXPANDERSRC	:=	$(addprefix $(SRCDIR)/$(EXPANDERDIR)/, $(addsuffix .c, $(EXPANDERSRC)))
EXECUTOBJ	:=	$(addprefix $(OBJDIR)/$(EXECUTDIR)/, $(addsuffix .o, $(EXECUTSRC)))
EXECUTSRC	:=	$(addprefix $(SRCDIR)/$(EXECUTDIR)/, $(addsuffix .c, $(EXECUTSRC)))

############## compilation ###############

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -lreadline #-g -fsanitize=address


C_LIBFT		=	make -C libft
C_PRINTF	=	make -C ft_printf
C_GNL		=	make -C gnl
AR_LIBFT	=	libft/libft.a
AR_PRINTF	=	ft_printf/libftprintf.a
AR_GNL		=	gnl/get_next_line

$(OBJDIR)/%.o:	$(SRCDIR)/%.c 
#	@echo "compile >>>>> $^"
	@printf "$(GREEN) compile >>>>> $(notdir $<) $(RESET)\n"
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(BUILTDIR)
	@mkdir -p $(OBJDIR)/$(LEXERDIR)
	@mkdir -p $(OBJDIR)/$(PARSERDIR)
	@mkdir -p $(OBJDIR)/$(EXPANDERDIR)
	@mkdir -p $(OBJDIR)/$(EXECUTDIR)
	@$(CC) $(CFALGS) $< -c -I $(INC) -o $@

all:	$(NAME)

$(NAME):	$(OBJ) $(BUILTOBJ) $(LEXEROBJ) $(PARSEROBJ) $(EXPANDEROBJ) $(EXECUTOBJ)
	@$(C_LIBFT) -s
	@$(C_PRINTF) -s
	@$(C_GNL) -s
	@$(CC) $(CFLAGS) $^ $(AR_LIBFT) $(AR_PRINTF) $(AR_GNL) -I $(INC) -o $@
	@printf "\n\n$(SPLASH) $(RED)              ------------- Minishell Ready -------------$(RESET)\n\n\n"

clean:
	@$(C_LIBFT) clean
	@$(C_PRINTF) clean
	@$(C_GNL) clean
	@rm -rf *.o
	@rm -rf $(OBJDIR)
	
fclean: clean

	@$(C_LIBFT) fclean
	@$(C_PRINTF) fclean
	@$(C_GNL) fclean
	@rm -rf $(NAME)

re:	fclean all

.PHONY:	all clean fclean re

