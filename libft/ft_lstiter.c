/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 22:35:39 by levensta          #+#    #+#             */
/*   Updated: 2020/11/08 15:08:29 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lst2;

	if (lst && f)
	{
		lst2 = lst;
		while (lst)
		{
			lst2 = lst->next;
			f(lst->content);
			lst = lst2;
		}
	}
}
