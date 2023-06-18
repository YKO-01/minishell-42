# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osajide <osajide@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/28 11:49:30 by osajide           #+#    #+#              #
#    Updated: 2023/06/12 16:20:50 by osajide          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CFLAGS = -Wall -Wextra -Werror
SRC = ft_putchar.c ft_putstr.c ft_putnbr.c ft_printf.c \
ft_unputnbr.c ft_upperhexa.c ft_lowerhexa.c ft_pointer.c
OBJ = $(SRC:.c=.o)
RM = rm -rf
AR = ar -rcs

all : $(NAME)

%.o : %.c
	@cc $(CFLAGS) -c $<

$(NAME) : $(OBJ)
	@$(AR) $@ $^

clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

