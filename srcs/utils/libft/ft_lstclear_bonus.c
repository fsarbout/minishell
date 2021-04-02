/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 15:52:20 by htagrour          #+#    #+#             */
/*   Updated: 2021/04/02 16:12:09 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*ptr1;

	ptr = *lst;
	if (ptr)
	{
		while (ptr)
		{
			ptr1 = ptr->next;
			(*del)(ptr->content);
			free(ptr);
			ptr = ptr1;
		}
		*lst = NULL;
	}
	return (0);
}
