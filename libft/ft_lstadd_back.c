/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:38:19 by levensta          #+#    #+#             */
/*   Updated: 2021/02/18 20:39:00 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst2;
	
	if (lst && new)
	{
		new->next = NULL;
		if (!(*lst))
			*lst = new;
		else
		{
			lst2 = *lst;
			while (lst2->next)
				lst2 = lst2->next;
			lst2->next = new;
		}
	}
}
