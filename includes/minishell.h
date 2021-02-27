/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:05:53 by fsarbout          #+#    #+#             */
/*   Updated: 2021/02/26 18:56:43 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <sys/types.h>
#include "structs.h"
#include "functions.h"
#include "macros.h"
#include "../srcs/parsing/stdin/in.h"
#include "../srcs/parsing/stdout/out.h"
#include "../libft/libft.h"    

#endif