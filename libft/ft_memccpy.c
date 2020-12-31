/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:33:48 by levensta          #+#    #+#             */
/*   Updated: 2020/11/06 13:54:03 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dest, const void *source, int ch, size_t n)
{
	size_t			i;
	unsigned char	*src;
	unsigned char	*dst;
	unsigned char	c;

	i = 0;
	c = (unsigned char)ch;
	dst = (unsigned char *)dest;
	src = (unsigned char *)source;
	if (n > 0)
	{
		while (i < n)
		{
			dst[i] = src[i];
			if (src[i] == c)
				return (&dst[i + 1]);
			i++;
		}
	}
	return (NULL);
}
