/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:59:17 by fsarbout          #+#    #+#             */
/*   Updated: 2021/04/03 17:18:35 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	sig_handler(int sig)
{
	if (g_var.flag)
	{
		if (sig != SIGINT)
			ft_putstr_fd("Quit: 3", STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	if (sig == SIGINT && !g_var.flag)
	{
		free(g_var.current->content);
		g_var.current->content = ft_strdup("");
		ft_putchar_fd('\n', STDOUT_FILENO);
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
