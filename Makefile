# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/25 20:02:45 by fsarbout          #+#    #+#              #
#    Updated: 2021/02/25 20:05:29 by fsarbout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc 

CFLAGS = -Wall -Wextra -Werror


SRC = *.c

all : $(NAME)

$(NAME): $(SRC)
	@cd libft && make re
	@$(CC) $(SRC) $(CFLAGS) -o $(NAME) $(_MLX_)
	
clean:
	@cd libft && make clean

fclean: clean
	@rm -rf $(NAME) 

re:	fclean all