/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:16:06 by fsarbout          #+#    #+#             */
/*   Updated: 2021/03/18 11:39:48 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

typedef struct s_var_bag
{
	int		brack_flag;
	char	prev_char;
	char	spec_char;
	int		slash_flag;
}				t_var_bag;

typedef struct s_redirection
{
	int		type;
	char	*file;
}				t_redx;

typedef struct s_command
{
	t_list	*args;
	int		next;
	t_list	*in_redx;
	t_list	*out_redx;
}				t_command;

int	g_flag;

#endif
