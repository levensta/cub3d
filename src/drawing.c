/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:34:56 by levensta          #+#    #+#             */
/*   Updated: 2021/01/29 22:49:00 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceil(t_all *cub, int column_h)
{
		float	j;
		int i;

		if (column_h < 0)
			column_h = 0;
		i = (cub->scene.screen_height - column_h) / 2;
		j = -1;
		while (j++ < i)
			my_mlx_pixel_put(cub, cub->x, j, cub->scene.ceiling);
}

void	draw_floor(t_all *cub, int column_h)
{
	int j;

	if (column_h < 0)
		column_h = 0;
	j = (cub->scene.screen_height + column_h) / 2 - 1;
	while (j++ < cub->scene.screen_height)
		my_mlx_pixel_put(cub, cub->x, j, cub->scene.flooring);
}

void	draw_texture(t_all *cub, float hit, int size, int n)
{
	unsigned int	color;
	float			j;
	int				i;
	int				max;

	i = (cub->scene.screen_height - size) / 2;
	j = 0;
	max = (cub->scene.screen_height + size) / 2;
	if (i < 0)
	{
		j = ((float)cub->txt[n].height / (float)size) * (-i);
		i = 0;
		max = cub->scene.screen_height;
	}
	hit *= cub->txt[n].width;
	while (i < max)
	{
		color = *(unsigned int*)(cub->txt[n].addr + ((int)j * cub->txt[n].line_length + (int)hit * (cub->txt[n].bits_per_pixel / 8)));
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
    t_sprite dp;
    int     tx;
    int     size;

	y1 = y1 + 0;
	x1 = x1 + 0;
    ang.x = cub->plr.route + 0.25f;
    if (ang.x > 1.0f)
        ang.x -= 1.0f;
    ang.x *= (2 * M_PI);
    dist.y = (cub->scene.screen_width / 2) / tan(((60.0f * M_PI / 180.0f) / 2));
    dp.x = cub->plr.x0 - (sprite.x + 0.5f);
    dp.y = cub->plr.y0 - (sprite.y + 0.5f);
    ang.y = atan2(dp.y, dp.x) - ang.x; // абсолютное направление от игрока до спрайта
    size = dist.y / (cosf(ang.y) * sprite.distance); // ширина и высота спрайта (квадратный)
    tx = cub->scene.screen_width / 2 + tan(ang.y) * dist.y - size / 2; // точка пересечения луча со спрайтом
  if (size <= 0 || tx >= cub->scene.screen_width \
	|| cub->x < tx || cub->x >= tx + size)
        return ;
	if (sprite.distance <= sqrtf(powf(x1 - cub->plr.x0, 2) + powf(y1 - cub->plr.y0, 2)))
    	draw_texture(cub, (cub->x - tx) / (float)size, size, 4);
}
