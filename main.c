/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:11:29 by fsarbout          #+#    #+#             */
/*   Updated: 2021/02/25 20:04:49 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int main(int ac, char ** av, char **env)
{
    char string = "echo hello world";
    
    printf("%s\n", string);
    return (0);
}