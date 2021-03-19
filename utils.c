/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:59:17 by fsarbout          #+#    #+#             */
/*   Updated: 2021/03/19 19:14:38 by htagrour         ###   ########.fr       */
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
