/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:34:56 by levensta          #+#    #+#             */
/*   Updated: 2021/02/16 20:44:01 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_column(float x, float y, t_all *cub)
{
	int		column_h;

	cub->dists[cub->x] = sqrtf(powf(x, 2) + powf(y, 2));
	cub->dists[cub->x] *= cosf(fabsf(cub->plr.route * 360.0f - cub->ray \
	* 360.0f) * (M_PI / 180.0f));
	column_h = cub->s_width / 2;
	column_h = (float)column_h / tanf((FOV * 360.0f / 2.0f) * (M_PI / 180.0f));
	column_h = (int)ceilf((float)column_h / cub->dists[cub->x]);
	return (column_h);
}

void		draw_ceil(t_all *cub, int column_h)
{
	int		i;
	float	j;

	if (column_h < 0)
		column_h = 0;
	i = (cub->s_height - column_h) / 2;
	j = -1;
	while (j++ < i)
		my_mlx_pixel_put(cub, cub->x, j, (unsigned int)cub->scene.ceiling);
}

void		draw_floor(t_all *cub, int column_h)
{
	int j;

	if (column_h < 0)
		column_h = 0;
	j = (cub->s_height + column_h) / 2 - 1;
	while (j++ < cub->s_height)
		my_mlx_pixel_put(cub, cub->x, j, (unsigned int)cub->scene.flooring);
}

void		draw_texture(t_all *cub, float hit, int size, int n)
{
	unsigned int	color;
	float			j;
	int				i;
	int				max;

	i = (cub->s_height - size) / 2;
	j = 0;
	max = (cub->s_height + size) / 2;
	if (i < 0)
	{
		j = ((float)cub->txt[n].height / (float)size) * (-i);
		i = 0;
		max = cub->s_height;
	}
	hit *= cub->txt[n].width;
	while (i < max)
	{
		color = *(unsigned int*)(cub->txt[n].addr + ((int)j * cub->txt[n].ll \
		+ (int)hit * (cub->txt[n].bpp / 8)));
		my_mlx_pixel_put(cub, cub->x, i, color);
		i++;
		j += (float)cub->txt[n].height / (float)size;
	}
}

void		drawing_room(t_all *cub, char is_x)
{
	cub->column_h = count_column(cub->plr.x0 - cub->x1, \
	cub->plr.y0 - cub->y1, cub);
	draw_ceil(cub, cub->column_h);
	draw_floor(cub, cub->column_h);
	if (is_x)
	{
		if (cub->ray >= 0 && cub->ray < 0.5f)
			draw_texture(cub, cub->y1 - floorf(cub->y1), cub->column_h, 2);
		else
			draw_texture(cub, ceilf(cub->y1) - cub->y1, cub->column_h, 3);
	}
	else
	{
		if (cub->ray >= 0.25f && cub->ray < 0.75f)
			draw_texture(cub, ceilf(cub->x1) - cub->x1, cub->column_h, 0);
		else
			draw_texture(cub, cub->x1 - floorf(cub->x1), cub->column_h, 1);
	}
}
