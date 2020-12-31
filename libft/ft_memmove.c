/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:24:51 by levensta          #+#    #+#             */
/*   Updated: 2020/11/06 13:49:42 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *source, size_t n)
{
	size_t	i;
	char	*src;
	char	*dst;

	i = 0;
	dst = (char *)dest;
	src = (char *)source;
	if (!dst && !src)
		return (0);
	if (dst < src)
		return (ft_memcpy(dest, source, n));
	while (n--)
		dst[n] = src[n];
	return (dest);
}
