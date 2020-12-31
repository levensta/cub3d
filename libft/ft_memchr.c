/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:57:06 by levensta          #+#    #+#             */
/*   Updated: 2020/11/06 18:34:42 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*str;
	char	ch;

	if (n != 0)
	{
		i = -1;
		str = (char *)s;
		ch = (char)c;
		while (++i < n)
			if (str[i] == ch)
				return (&str[i]);
	}
	return (NULL);
}
