/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:19:47 by levensta          #+#    #+#             */
/*   Updated: 2020/11/07 14:38:23 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	int		del;
	int		check_minus;

	i = n;
	check_minus = 1;
	del = 1;
	if (i < 0 && (check_minus = -1))
		ft_putchar_fd('-', fd);
	while (i / 10)
	{
		del *= 10;
		i /= 10;
	}
	i = 0;
	while (del / 10)
	{
		ft_putchar_fd((n / del) * check_minus + '0', fd);
		n = n - (n / del) * del;
		del /= 10;
	}
	ft_putchar_fd((n / del) * check_minus + '0', fd);
}
