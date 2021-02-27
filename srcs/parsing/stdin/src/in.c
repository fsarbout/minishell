/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:32:12 by ielbadao          #+#    #+#             */
/*   Updated: 2021/02/26 12:27:04 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../in.h"

void	fill_line(char **line, char *buffer)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin2(*line, buffer);
	ft_free(&tmp);
}

int		process_line(char **line, char **remain)
{
	char	*nl;
	char	*tmp;

	if ((nl = ft_strchr2(*line, '\n')))
	{
		*nl = '\0';
		tmp = *line;
		*line = ft_strdup2(*line);
		*remain = ft_strdup2(nl + 1);
		ft_free(&tmp);
		return (1);
	}
	return (0);
}

int		process_remain(char **remain, char **line)
{
	char	*nl;
	char	*tmpr;
	char	*tmpl;

	if ((nl = ft_strchr2(*remain, '\n')))
	{
		*nl = '\0';
		tmpl = *line;
		tmpr = *remain;
		*line = ft_strdup2(*remain);
		*remain = ft_strdup2(nl + 1);
		ft_free(&tmpl);
		ft_free(&tmpr);
		return (1);
	}
	tmpl = *line;
	*line = ft_strdup2(*remain);
	ft_free(&tmpl);
	ft_free(remain);
	return (0);
}

int		in(int fd, char **line)
{
	static char *remain[256];
	char		*buffer;
	int			bytes;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (read(fd, NULL, 0) || BUFFER_SIZE < 0 || !line || !buffer)
		return (-1);
	*line = ft_strdup2("\0");
	if (remain[fd] && process_remain(&remain[fd], line))
	{
		ft_free(&buffer);
		return (1);
	}
	while ((bytes = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[bytes] = '\0';
		fill_line(line, buffer);
		if (process_line(line, &remain[fd]))
		{
			ft_free(&buffer);
			return (1);
		}
	}
	ft_free(&buffer);
	return (0);
}
