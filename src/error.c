/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:13:43 by levensta          #+#    #+#             */
/*   Updated: 2021/01/13 23:13:54 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(int code)
{
	write(1, "Error\n", 6);
	if (code == 1)
		write(1, "Your file does not exist or file extension is not .cube\n", 56);
	else if (code == 2)
		write(1, "Check your screen resolution\n", 29);
	else if (code == 3)
		write(1, "Check your paths of textures\n", 29);
	else if (code == 4)
		write(1, "Check your RGB params\n", 22);
	else if (code == 5)
		write(1, "Invalid map\n", 12);
	else if (code == 101)
		write(1, "You're crazy. Error of malloc\n", 30);
	// очистить все, что только можно
	exit(code);
}
