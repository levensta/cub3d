/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:35:39 by levensta          #+#    #+#             */
/*   Updated: 2021/02/17 23:32:37 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	y_set(t_all *cub, int size, double *ty, t_sprite *d)
{
	int		y;

	y = (cub->s_height - size) / 2;
	y += (double)size / (double)cub->s_height;
	*ty = 0.0f;
	d->x = (double)cub->txt[4].width / (double)size;
	d->y = (double)cub->txt[4].height / (double)size;
	if (y < 0)
	{
		*ty = d->y * (double)(-y);
		y = -1;
	}
	return (y);
}

void		draw_sprite(t_all *cub, t_sprite sp, int x_start, int x)
{
	t_sprite		d;
	double			ty;
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
			cub->txt[4].ll + (int)((double)x * d.x) * (cub->txt[4].bpp / 8)));
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
	double		ang;
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
		cub->sprite[i].angle = atan2(dt.y, dt.x) - ang;
		cub->sprite[i].size = cub->view_dist / (cos(cub->sprite[i].angle) \
		* cub->sprite[i].distance);
		tx = cub->s_width / 2 + (tan(cub->sprite[i].angle) * cub->view_dist) \
		- cub->sprite[i].size / 2;
		if (cub->sprite[i].size <= 0 || tx >= cub->s_width)
			continue ;
		draw_sprite(cub, cub->sprite[i], tx, -1);
	}
}
