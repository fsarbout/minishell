/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 18:40:20 by htagrour          #+#    #+#             */
/*   Updated: 2021/03/29 19:13:41 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **lst, void (*del)(void*))
{	
	if (*lst && del)
	{
		(*del)((*lst)->content);
		*lst = (*lst)->next;
		(*lst)->prev = NULL;
	}
}
