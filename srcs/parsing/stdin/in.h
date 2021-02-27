/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:28:54 by ielbadao          #+#    #+#             */
/*   Updated: 2021/02/26 12:26:02 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IN_H
# define IN_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# define BUFFER_SIZE 4096

char		*ft_strchr2(const char *s, int c);
int			ft_strlen2(const char *str);
char		*ft_strjoin2(char const *s1, char const *s2);
char		*ft_strdup2(const char *s);
void		ft_free(char **p);
void		fill_line(char **line, char *buffer);
int			process_line(char **line, char **remain);
int			process_remain(char **remain, char **line);
int			in(int fd, char **line);
#endif
