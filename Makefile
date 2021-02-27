# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/25 20:02:45 by fsarbout          #+#    #+#              #
#    Updated: 2021/02/26 19:03:04 by fsarbout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc 

CFLAGS = -Wall -Wextra -Werror 
#SANITIZER = -fsanitize=address

 
SRC = *.c\
	 ./srcs/parsing/stdin/src/*.c\
	 ./srcs/parsing/stdout/src/*.c\
	 ./libft/*.c

	 

all : $(NAME)

$(NAME): $(SRC)
	@cd libft && make re
	@$(CC) $(SRC) $(CFLAGS) -o $(NAME) $(SANITIZER)
	
clean:
	@cd libft && make fclean

fclean: clean
	@rm -rf $(NAME) 

re:	fclean all