/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 18:25:54 by levensta          #+#    #+#             */
/*   Updated: 2020/11/23 22:44:01 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int i;
	int nb;
	int check_symbol;
	int amount;

	i = 0;
	nb = 0;
	check_symbol = 1;
	amount = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
	|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-' && ++i)
		check_symbol = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		amount += (nb == 0) ? 0 : 1;
		if (amount > 19)
			return ((check_symbol > 0) ? -1 : 0);
		i++;
	}
	return (nb * check_symbol);
}
