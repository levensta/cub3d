/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:28:21 by levensta          #+#    #+#             */
/*   Updated: 2021/02/08 20:07:51 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_all *cub, int x, int y, unsigned int color)
{
    char	*dst;
	if (x < 0 || y < 0 || x >= cub->s_width || y >= cub->s_height)
		return ;
	dst = cub->win.addr + (y * cub->win.ll + x * (cub->win.bpp / 8));
	// dst = cub->screen.data + (y * cub->s_width + x) * 4;
	*(unsigned int*)dst = color;
}

void	ray_correct(float *ray)
{
	while (*ray < 0.0f)
		*ray += 1;
    while (*ray >= 1.0f)
		*ray -= 1;
}

void	clear_image(t_all *cub)
{
	int x;
	int y;
	x = -1;
	while (++x < cub->s_width)
	{
		y = -1;
		while (++y < cub->s_height)
			my_mlx_pixel_put(cub, x, y, 0);
	}
}

int	count_column(float x, float y, t_all *cub)
{
	int		column_h;
	
	cub->dists[cub->x] = sqrtf(powf(x, 2) + powf(y, 2));
	cub->dists[cub->x] *= cosf(fabsf(cub->plr.route * 360.0f - cub->ray * 360.0f) \
	* (M_PI / 180.0f));
	column_h = cub->s_width / 2;
	column_h = (float)column_h / tanf((FOV * 360.0f / 2.0f) * (M_PI / 180.0f));
	column_h = (int)ceilf((float)column_h / cub->dists[cub->x]);
	return (column_h);
}
