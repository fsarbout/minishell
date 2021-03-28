/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 21:52:32 by htagrour          #+#    #+#             */
/*   Updated: 2021/03/28 15:00:41 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	isthereaback(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '\n')
			return (1);
		index++;
	}
	return (0);
}

int	free_(char **str)
{
	free(*str);
	*str = NULL;
	return (0);
}

int	add_line(char **str, int fd)
{
	char	*tem;
	int		i;
	char	*ptr;

	i = 1;
	while (i > 0)
	{
		tem = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		i = read(fd, tem, BUFFER_SIZE);
		if (i == -1)
			return (-1);
		tem[i] = '\0';
		ptr = *str;
		*str = ft_strjoin(*str, tem);
		if (!*str)
			return (-1);
		free_(&ptr);
		free_(&tem);
		if (isthereaback(*str))
			break ;
		// if (**str)
		// 	i = 1;
	}
	return (i);
}

int	get_next_line(int fd, char **line)
{
	static char	*rest;
	int			counter;
	int			read_value;
	char		*ptr;

	counter = 0;
	if (!rest)
		rest = ft_strdup("");
	read_value = add_line(&rest, fd);
	if (read_value == -1)
		return (-1);
	while (rest[counter] != '\n' && rest[counter])
		counter++;
	*line = ft_substr(rest, 0, counter);
	if (!*line)
		return (-1);
	if (rest[counter] != '\n' && !read_value)
		return (free_(&rest));
	ptr = rest;
	rest = ft_strdup(rest + counter + 1);
	if (!rest)
		return (-1);
	free_(&ptr);
	return (1);
}
