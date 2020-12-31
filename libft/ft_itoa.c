/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:23:53 by levensta          #+#    #+#             */
/*   Updated: 2020/11/07 13:03:59 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	int		i;
	int		nb;
	char	*str;
	int		check_minus;

	i = 1;
	nb = n;
	check_minus = 1;
	while (n / 10 != 0 && i++)
		n = (n / 10);
	if (nb < 0 && i++)
		check_minus = -1;
	if (!(str = (char *)malloc((i + 1))))
		return (NULL);
	str[i] = '\0';
	while (i-- > 0)
	{
		str[i] = (nb % 10) * check_minus + '0';
		nb = nb / 10;
	}
	if (check_minus == -1)
		str[++i] = '-';
	return (str);
}
