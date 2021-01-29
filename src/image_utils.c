/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:28:21 by levensta          #+#    #+#             */
/*   Updated: 2021/01/29 22:47:00 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_all *cub, int x, int y, unsigned int color)
{
    char	*dst;
	if (x < 0 || y < 0 || x >= cub->scene.screen_width || y >= cub->scene.screen_height)
		return ;
	dst = cub->win.addr + (y * cub->win.line_length + x * (cub->win.bits_per_pixel / 8));
	// dst = cub->screen.data + (y * cub->s_width + x) * 4;
	*(unsigned int*)dst = color;
}

void	ray_correct(float *ray)
{
	while (*ray < 0)
		*ray += 1;
    while (*ray >= 1)
		*ray -= 1;
}

void	clear_image(t_all *cub)
{
	int x;
	int y;
	x = -1;
	while (++x < cub->scene.screen_width)
	{
		y = -1;
		while (++y < cub->scene.screen_height)
			my_mlx_pixel_put(cub, x, y, 0);
	}
}

float	count_distance(float x, float y, float route, float ray)
{
	float distance;

	distance = sqrtf(powf(x, 2) + powf(y, 2));
	distance = distance * cosf(fabsf(route * 360.0f - ray * 360.0f) * (M_PI / 180.0f));
	return (distance);
}

int	count_column(float x, float y, t_all *cub)
{
	float	distance;
	int		column_h;
	
	distance = count_distance(x, y, cub->plr.route, cub->ray);
	column_h = cub->scene.screen_height / 2;
	column_h = (float)column_h / tanf((FOV * 360.0f / 2.0f) * (M_PI / 180.0f));
	column_h = (int)ceilf((float)column_h / distance);
	return (column_h);
}
