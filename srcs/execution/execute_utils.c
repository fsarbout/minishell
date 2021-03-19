/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 09:08:28 by fsarbout          #+#    #+#             */
/*   Updated: 2021/03/19 18:13:19 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_buitin1(char *str)
{
	if (!strcmp(str, "cd"))
		return (1);
	if (!strcmp(str, "export"))
		return (2);
	if (!strcmp(str, "unset"))
		return (3);
	if (!strcmp(str, "exit"))
		return (4);
	return (-1);
}

int	is_buitin2(char *str)
{
	if (!strcmp(str, "echo"))
		return (1);
	if (!strcmp(str, "pwd"))
		return (2);
	if (!strcmp(str, "env"))
		return (3);
	return (-1);
}

int	is_built_in(char *str)
{
	return (is_buitin1(str) != -1 || is_buitin2(str) != -1);
}
