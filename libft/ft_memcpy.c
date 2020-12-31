/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 23:13:41 by levensta          #+#    #+#             */
/*   Updated: 2020/11/06 13:53:06 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dest, const void *source, size_t n)
{
	size_t	i;
	char	*src;
	char	*dst;

	i = 0;
	dst = (char *)dest;
	src = (char *)source;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dest);
}
