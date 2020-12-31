/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:11:55 by levensta          #+#    #+#             */
/*   Updated: 2020/11/08 15:06:05 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lst2;
	t_list	*lst3;

	if (lst && *lst && del)
	{
		lst2 = *lst;
		while (lst2)
		{
			lst3 = lst2->next;
			ft_lstdelone(lst2, del);
			lst2 = lst3;
		}
	}
	*lst = 0;
}
