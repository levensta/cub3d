/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:38:19 by levensta          #+#    #+#             */
/*   Updated: 2021/02/21 17:59:46 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_tmp;

	if (lst && *lst)
	{
		lst_tmp = *lst;
		while (lst_tmp->next)
			lst_tmp = lst_tmp->next;
		lst_tmp->next = new;
	}
	else
		*lst = new;
}
