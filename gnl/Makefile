# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/04 10:06:27 by ayakoubi          #+#    #+#              #
#    Updated: 2023/03/04 10:06:59 by ayakoubi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= get_next_line

SRC	= get_next_line get_next_line_utils

SRCS	= $(addsuffix .c, $(SRC));

OBJ	= $(addsuffix .o, $(SRC));

CC 	= gcc
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@ar -rcs $@ $^

clean:	
	@rm -rf *.o

fclean:	clean
	@rm -rf $(NAME)

re:	fclean re

.PHONY: all clean fclean re
