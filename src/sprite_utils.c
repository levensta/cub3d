/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:42:05 by levensta          #+#    #+#             */
/*   Updated: 2021/01/31 18:31:17 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int	find_repeat_spr(t_all *cub, int x1, int y1)
// {
// 	int i;

// 	i = 0;
// 	while (i < cub->num_spr)
// 	{
// 		if ((int)cub->sprite[i].x == x1 && (int)cub->sprite[i].y == y1)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

int		count_sprites(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '2')
			count++;
		i++;
	}
	return (count);
}

void		find_sprite(t_all *cub, int x1, int y1)
{
	int i;

	i = 0;
	// if (find_repeat_spr(cub, x1, y1))
	// 	return ;
	cub->sprite[cub->num_spr].x = (float)x1 + 0.5f;
	cub->sprite[cub->num_spr].y = (float)y1 + 0.5f;
	cub->num_spr++;
}

void		find_dists(t_all *cub)
{
	int		i;
	float	x1;
	float	y1;

	i = -1;
	while (++i < cub->num_spr)
	{
		x1 = cub->sprite[i].x;
		y1 = cub->sprite[i].y;
		cub->sprite[i].distance = sqrtf(powf(cub->plr.x0 - x1, 2) + powf(cub->plr.y0 - y1, 2));
	}
}

void		sort_sprites(t_all *cub)
{
	t_sprite tmp;
	int		i;
	int		j;
	char	flag;

	i = 0;
	while (i < cub->num_spr)
	{
		flag = 1;
		j = 0;
		while (j < cub->num_spr - (i + 1))
		{
			if (cub->sprite[j].distance < cub->sprite[j + 1].distance)
			{
				flag = 0;
				tmp = cub->sprite[j];
				cub->sprite[j] = cub->sprite[j + 1];
				cub->sprite[j + 1] = tmp;
			}
			j++;
		}
		if (flag)
			break;
		i++;
	}
}

