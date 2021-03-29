/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 22:24:08 by htagrour          #+#    #+#             */
/*   Updated: 2021/03/29 19:03:35 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
#include <termios.h>
#include <termcap.h>
#include "../../../includes/minishell.h"
#include "../libft/libft.h"
# define BUFFER_SIZE 1
#define CTR_D 4
#define DELETE 127
#define ARROW_UP 183
#define ARROW_DOWN 184
// #define ARROW_RIGHT 185
// #define ARROW_LEFT 186
#define TAB 9

// typedef int
void                refresh(t_list *current);
int                 put_char(int i);
char                *all_char(int c);
int					get_next_line(int fd, char **line);
void                just_print(void *content);
int                 get_line(char **line, int fd, t_list *hist);

#endif
