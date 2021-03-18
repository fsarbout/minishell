/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:33:00 by fsarbout          #+#    #+#             */
/*   Updated: 2021/03/18 10:51:59 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

void	key_value(char *key, char *value, char **dist, int *i)
{
	char	*temp;

	if (value)
	{
		temp = ft_strjoin(key, "=");
		*dist = ft_strjoin(temp, value);
		free(temp);
		*i = *i + 1;
	}
}
/*
   if flag == 1 this function will retun array of key
   else will retunr array of key=value
   */

char	**hash_to_arr(t_hash_map *hm, int flag)
{
	char	**tab;
	t_listo	*temp;
	int		i;
	int		size;

	i = 0;
	size = hm->size;
	tab = malloc(sizeof(char*) * (hm->elem_total + 1));
	if (!tab)
		return (NULL);
	while (--size >= 0)
	{
		temp = hm->item[size];
		while (temp)
		{
			if (temp->key && strcmp(temp->key, "?"))
			{
				if (flag)
					tab[i++] = ft_strdup(temp->key);
				else
					key_value(temp->key, temp->value, &tab[i], &i);
			}
			temp = temp->next;
		}
	}
	tab[i] = NULL;
	return (tab);
}

char	**sorted_key(t_hash_map *hm)
{
	char	**tab;

	tab = hash_to_arr(hm, 1);
	if (!tab)
		return (NULL);
	bubblesort(tab, hm->elem_total - 1);
	return (tab);
}

int	free_hash_map(t_hash_map *hm)
{
	t_listo	*temp;
	t_listo	*temp1;

	while (--hm->size >= 0)
	{
		temp = hm->item[hm->size];
		while (temp)
		{
			temp1 = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			temp = temp1;
		}
		hm->item[hm->size] = NULL;
	}
	free(hm->item);
	free(hm);
	return (1);
}

unsigned int	hash(const char *str, int size)
{
	unsigned int	hash;

	hash = 0;
	while (str && *str)
	{
		hash = (hash + *str) % size;
		str++;
	}
	return (hash);
}

t_hash_map	*init_hash_map(int size)
{
	t_hash_map	*hm;

	if (!(hm = malloc(sizeof(t_hash_map))))
		return (NULL);
	hm->item = malloc(sizeof(t_listo*) * size);
	if (hm->item == NULL)
		return (NULL);
	bzero(hm->item, sizeof(t_listo*) * size);
	hm->size = size;
	hm->elem_total = 0;
	return (hm);
}
