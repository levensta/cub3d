/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:41:24 by levensta          #+#    #+#             */
/*   Updated: 2020/12/20 16:01:35 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
}

void	ft_putnbr(int n)
{
	int		i;
	int		del;
	int		check_minus;

	i = n;
	check_minus = 1;
	del = 1;
	if (i < 0 && (check_minus = -1))
		ft_putchar('-');
	while (i / 10)
	{
		del *= 10;
		i /= 10;
	}
	i = 0;
	while (del / 10)
	{
		ft_putchar((n / del) * check_minus + '0');
		n = n - (n / del) * del;
		del /= 10;
	}
	ft_putchar((n / del) * check_minus + '0');
}

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int		get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}