/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:11:29 by fsarbout          #+#    #+#             */
/*   Updated: 2021/02/27 08:29:24 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(/* int ac, char ** av, char **env */)
{
    int		elements;
    char 	*line;
    char 	**cmd_line;

    int i = 0;
    out("minishell$ ");
	in(0, &line);
    // cmd_line = line
    // if (!ft_strncmp(line, "ls -ls", ft_strlen("ls -la")))
    //     printf("nnbeg\n");
    printf("line == %s\n" , line);
    cmd_line = ft_split(line ,32);
    // ft_putstr("minishell$ ");
    elements = lenght(cmd_line);
    while (elements)
    {
        printf("%s\n", cmd_line[i]);
        elements--;
        i++;
    }
    // printf("%s\n", line);
    return (0);
}

int             lenght(char **str)
{
        int     n;

        n = 0;
        while (str[n])
                n++;
        return (n);
}
