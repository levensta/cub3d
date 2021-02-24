/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:24:51 by levensta          #+#    #+#             */
/*   Updated: 2021/02/24 21:20:38 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *source, size_t n)
{
	char	*src;
	char	*dst;

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
