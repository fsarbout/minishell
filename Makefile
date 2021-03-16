# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 16:29:25 by htagrour          #+#    #+#              #
#    Updated: 2021/03/16 12:44:24 by fsarbout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -fsanitize=address

CFLAGS = -Wall -Wextra -Werror

SRC = 	srcs/utils/get_line/*.c\
		srcs/utils/libft/*.c\
		srcs/utils/hash_table/*.c\
		srcs/utils/*.c\
		srcs/parsing/*.c\
		srcs/execution/*.c\
		main.c

all : $(NAME)

$(NAME): $(SRC)
	@$(CC) $(SRC) -o $(NAME) -g
	
clean:
	@rm -rf *.o minishell.a

fclean: clean
	@rm -rf $(NAME) 

re:	fclean all
	
