/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:34:56 by levensta          #+#    #+#             */
/*   Updated: 2021/02/07 22:09:04 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceil(t_all *cub, int column_h)
{
		float	j;
		int i;

		if (column_h < 0)
			column_h = 0;
		i = (cub->s_height - column_h) / 2;
		j = -1;
		while (j++ < i)
			my_mlx_pixel_put(cub, cub->x, j, cub->scene.ceiling);
}

void	draw_floor(t_all *cub, int column_h)
{
	int j;

	if (column_h < 0)
		column_h = 0;
	j = (cub->s_height + column_h) / 2 - 1;
	while (j++ < cub->s_height)
		my_mlx_pixel_put(cub, cub->x, j, cub->scene.flooring);
}

void	draw_texture(t_all *cub, float hit, int size, int n)
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
		color = *(unsigned int*)(cub->txt[n].addr + ((int)j * cub->txt[n].line_length + (int)hit * (cub->txt[n].bpp / 8)));
		if (color != 0 && color != 0xFF000000)
			my_mlx_pixel_put(cub, cub->x, i, color);
		i++;
		j += (float)cub->txt[n].height / (float)size;
	}
}

void        draw_sprite(t_all *cub, t_sprite sprite, float x1, float y1)
{
    t_sprite ang;
    t_sprite dist;
    t_sprite dt;
    float     tx;
    float     size;
	x1 = y1;

    ang.x = cub->plr.route + 0.25f;
	ray_correct(&ang.x);
    ang.x *= (2 * M_PI);
    dist.y = (cub->s_width / 2) / tanf(((60.0f * M_PI / 180.0f) / 2)); 
    dt.x = cub->plr.x0 - (sprite.x);
    dt.y = cub->plr.y0 - (sprite.y);
    ang.y = atan2f(dt.y, dt.x) - ang.x; // абсолютное направление от игрока до спрайта // угол спрайта относительно угла обзора
    size = dist.y / (cosf(ang.y) * sprite.distance); // ширина и высота спрайта (квадратный)
    tx = cub->s_width / 2 + tanf(ang.y) * dist.y - size / 2; // точка пересечения луча со спрайтом
	if (size <= 0 || tx > cub->s_width)
		return ;
	draw_sprite2(cub, size, tx, sprite.distance);
}

int			d_set(t_all *cub, int size, float *ty, t_sprite *d)
{
	int			y;
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


void		draw_sprite2(t_all *cub, int size, int x_start, float dist)
{
	t_sprite		d;
	float			ty;
	unsigned int	color;

	int y_start, y, x;
	y_start = d_set(cub, size, &ty, &d); 
	y = -1;
	while (++y < size && y + y_start < cub->s_height \
	&& ty < cub->txt[4].height)
	{
		x = -1;
		if (x_start < 0)
			x += -x_start;
		while (++x < size && x_start + x < cub->s_width)
		{
			color = *(unsigned int*)(cub->txt[4].addr + ((int)ty * cub->txt[4].line_length + (int)((float)x * d.x) * (cub->txt[4].bpp / 8)));
			if (color != 0 \
			 && cub->dists[x_start + x] >= dist - 0.5f
			&& color != 0xFF000000)
				my_mlx_pixel_put(cub, x_start + x, y_start + y, color);
		}
		ty += d.y;
	}
}
