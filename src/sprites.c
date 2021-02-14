/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:35:39 by levensta          #+#    #+#             */
/*   Updated: 2021/02/14 18:10:34 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	y_set(t_all *cub, int size, float *ty, t_sprite *d)
{
	int		y;

	y = (cub->s_height - size) / 2;
	y += (float)size / (float)cub->s_height;
	*ty = 0.0f;
	d->x = (float)cub->txt[4].width / (float)size;
	d->y = (float)cub->txt[4].height / (float)size;
	if (y < 0)
	{
		*ty = d->y * (float)(-y);
		y = -1;
	}
	return (y);
}

void		draw_sprite(t_all *cub, t_sprite sp, int x_start, int x)
{
	t_sprite		d;
	float			ty;
	unsigned int	color;
	int				y_start;
	int				y;

	if (x_start < 0)
		x += -x_start;
	while (++x < sp.size && x_start + x <= cub->s_width)
	{
		y_start = y_set(cub, sp.size, &ty, &d);
		y = -1;
		while (++y < sp.size && y + y_start < cub->s_height \
		&& ty < cub->txt[4].height)
		{
			color = *(unsigned int*)(cub->txt[4].addr + ((int)ty * \
			cub->txt[4].ll + (int)((float)x * d.x) * (cub->txt[4].bpp / 8)));
			if (color != 0 && color != 0xFF000000 && \
			cub->dists[x_start + x] >= sp.distance - 0.5f)
				my_mlx_pixel_put(cub, x_start + x, y_start + y, color);
			ty += d.y;
		}
	}
}

void		drawing_sprites(t_all *cub)
{
	t_sprite	dt;
	float		ang;
	int			tx;
	int			i;

	i = -1;
	ang = cub->plr.route + 0.25f;
	ray_correct(&ang);
	ang *= (2 * M_PI);
	while (++i < cub->num_spr)
	{
		dt.y = cub->plr.y0 - cub->sprite[i].y;
		dt.x = cub->plr.x0 - cub->sprite[i].x;
		cub->sprite[i].angle = atan2f(dt.y, dt.x) - ang;
		cub->sprite[i].size = cub->view_dist / (cosf(cub->sprite[i].angle) \
		* cub->sprite[i].distance);
		tx = cub->s_width / 2 + (tanf(cub->sprite[i].angle) * cub->view_dist) \
		- cub->sprite[i].size / 2;
		if (cub->sprite[i].size <= 0 || tx >= cub->s_width)
			continue ;
		draw_sprite(cub, cub->sprite[i], tx, -1);
	}
}
