/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:27:58 by fsarbout          #+#    #+#             */
/*   Updated: 2021/03/18 10:58:47 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_bin(char *cmd, struct stat st, t_hash_map *env)
{
	char	*temp1;
	char	**temp;
	char	*path;
	int		i;

	path = get_value("PATH", env);
	if (path[0])
	{
		temp = ft_split(path, ':');
		free(path);
		i = -1;
		while (temp[++i])
		{
			temp1 = temp[i];
			temp[i] = ft_add_char(temp[i], '/');
			free(temp1);
			temp1 = ft_strjoin(temp[i], cmd);
			if (!stat(temp1, &st) && (st.st_mode & S_IXUSR))
				return (temp1);
			free(temp1);
		}
		free_array((void**)temp);
	}
	else
		free(path);
	return (NULL);
}

int	get_full_path(t_command *command, t_hash_map *env)
{
	char	*cmd;
	char	*bin;
	struct stat	st;

	if (!command->args)
		return (1);
	cmd = (char *)command->args->content;
	if (is_built_in(cmd) || (!stat(cmd, &st) && (st.st_mode & S_IXUSR)))
		return (0);
	if (!(bin = get_bin(cmd, st, env)))
		return (127);
	free(command->args->content);
	command->args->content = (void *)ft_strdup(bin);
	free(bin);
	return (0);
}

int	get_in_fd(t_command command, int *last_fd)
{
	t_list	*temp;
	t_redx	*red;
	int		fd;

	fd = *last_fd;
	temp = command.in_redx;
	while (temp)
	{
		red = (t_redx*)temp->content;
		if ((fd = open(red->file, O_RDONLY)) < 0)
			return (-1);
		close(*last_fd);
		*last_fd = fd;
		temp = temp->next;
	}
	return (0);
}

int	get_out_fd(t_command command, int *out_fd)
{
	t_list	*temp;
	int		fd;
	t_redx	*red;

	fd = *out_fd;
	temp = command.out_redx;
	while (temp)
	{
		red = (t_redx*)temp->content;
		if (red->type)
			fd = open(red->file, O_RDWR | O_CREAT | O_APPEND, 0644);
		else
			fd = open(red->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (-1);
		close(*out_fd);
		*out_fd = fd;
		temp = temp->next;
	}
	return (0);
}
