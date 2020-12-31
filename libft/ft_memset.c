/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 22:11:01 by levensta          #+#    #+#             */
/*   Updated: 2020/11/04 22:30:59 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *dest, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)dest;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (str);
}
