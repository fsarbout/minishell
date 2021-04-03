# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 16:29:25 by htagrour          #+#    #+#              #
#    Updated: 2021/04/03 17:24:30 by fsarbout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -g -ltermcap
LIBFT=srcs/utils/libft/libft.a
CFLAGS = -Wall -Wextra -Werror 

SRC = srcs/execution/builtin_func.c\
	srcs/execution/builtin_utils.c\
	srcs/execution/builtins.c\
	srcs/execution/execute.c\
	srcs/execution/execute_utils.c\
	srcs/execution/execution.c\
	srcs/execution/utils.c\
	srcs/utils/updated_split.c\
	srcs/utils/utils.c\
	srcs/utils/utils2.c\
	srcs/utils/get_line/can_get_line.c\
	srcs/utils/get_line/utils.c\
	srcs/utils/hash_table/hash_table.c\
	srcs/utils/hash_table/hash_utils.c\
	srcs/utils/hash_table/extra_utils.c\
	srcs/parsing/get_args.c\
	srcs/parsing/parse.c\
	srcs/parsing/parse_utils.c\
	main.c\
	utils.c
	
all : $(NAME)

$(NAME): $(SRC)
	@cd srcs/utils/libft && make re
	@$(CC) $(CFLAGS) $(LIBFT) $(SRC) -o $(NAME) -g
	
clean:
	@cd srcs/utils/libft && make clean
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME) 

re:	fclean all
	
