/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:13:43 by levensta          #+#    #+#             */
/*   Updated: 2021/01/22 21:33:23 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(int code)
{
	ft_putstr_fd("Error\n", 1);
	if (code == 1)
		ft_putstr_fd("File extension is not .cube\n", 1);
	else if (code == 2)
		ft_putstr_fd("Check your screen resolution\n", 1);
	else if (code == 3)
		ft_putstr_fd("Check your paths of textures\n", 1);
	else if (code == 4)
		ft_putstr_fd("Check your RGB params\n", 1);
	else if (code == 5)
		ft_putstr_fd("Invalid map5555\n", 1);
	else if (code == 6)
		ft_putstr_fd("Your map contains a forbidden characters\n", 1);
	else if (code == 7)
		ft_putstr_fd("Your map contains a not only player\n", 1);
	else if (code == 8)
		ft_putstr_fd("Your map is incomplete\n", 1);
	else if (code == 100)
		ft_putstr_fd("Such file does not exist\n", 1);
	else if (code == 101)
		ft_putstr_fd("You're crazy. Error of malloc\n", 1);
	// очистить все, что только можно
	exit(code);
}
