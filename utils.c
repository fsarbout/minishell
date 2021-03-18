/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:59:17 by fsarbout          #+#    #+#             */
/*   Updated: 2021/03/18 12:13:16 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	sig_handler(int sig)
{
	ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
	if (sig == SIGINT && !g_flag)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		print_shell();
	}
}

void	ignore_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

void	get_external_env(char **envs, t_hash_map *env)
{
	char	**temp;

	while (*envs)
	{
		temp = ft_split(*envs, '=');
		set_value(temp[0], temp[1], env);
		free_array((void**)temp);
		envs++;
	}
}

int	free_error(char **str, t_hash_map *env)
{
	free_array((void**)str);
	print_error("syntax error", 258, env);
	return (1);
}

int	process_line(char *line, t_hash_map *env)
{
	t_command	*commands;
	char		**temp1;
	char		**temp2;
	int			i;
	int			total;

	temp1 = updated_split(line, ';', &i);
	if (!temp1)
		return (print_error("syntax error", 258, env));
	i = -1;
	while (temp1[++i])
	{
		temp2 = updated_split(temp1[i], '|', &total);
		if (!temp2)
			return (free_error(temp1, env));
		if (!(commands = get_commands(temp2, total, env)))
			return (free_array((void**)temp1));
		execute_commands(commands, 0, total, env);
		free_command_array(commands, total);
	}
	free_array((void**)temp1);
	return (0);
}
