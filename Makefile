# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 16:29:25 by htagrour          #+#    #+#              #
#    Updated: 2021/03/31 17:44:08 by htagrour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -g -ltermcap

CFLAGS = -Wall -Wextra -Werror

SRC = 	srcs/utils/get_line/*.c\
		srcs/utils/libft/*.c\
		srcs/utils/hash_table/*.c\
		srcs/utils/*.c\
		srcs/parsing/*.c\
		srcs/execution/*.c\
		test.c\
		main.c\
		utils.c

all : $(NAME)

$(NAME): $(SRC)
	@$(CC) $(SRC) -o $(NAME) -g
	
clean:
	@rm -rf *.o minishell.a

fclean: clean
	@rm -rf $(NAME) 

re:	fclean all
	
