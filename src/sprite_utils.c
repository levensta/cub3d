/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:42:05 by levensta          #+#    #+#             */
/*   Updated: 2021/02/14 16:35:52 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_repeat_spr(t_all *cub, int x1, int y1)
{
	int i;

	i = 0;
	while (i < cub->num_spr)
	{
		if ((int)floorf(cub->sprite[i].x) == x1 \
		&& (int)floorf(cub->sprite[i].y) == y1)
			return (1);
		i++;
	}
	return (0);
}

int			count_sprites(char *str)
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
	if (find_repeat_spr(cub, x1, y1))
		return ;
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
		cub->sprite[i].distance = sqrtf(powf(x1 - cub->plr.x0, 2) + \
		powf(y1 - cub->plr.y0, 2));
	}
}

void		sort_sprites(t_all *cub)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = 0;
	while (i < cub->num_spr - 1)
	{
		j = cub->num_spr - 1;
		while (j > i)
		{
			if (cub->sprite[j - 1].distance < cub->sprite[j].distance)
			{
				tmp = cub->sprite[j - 1];
				cub->sprite[j - 1] = cub->sprite[j];
				cub->sprite[j] = tmp;
			}
			j--;
		}
		i++;
	}
}
