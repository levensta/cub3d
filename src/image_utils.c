/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:28:21 by levensta          #+#    #+#             */
/*   Updated: 2021/02/12 23:34:55 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_all *cub, int x, int y, unsigned int color)
{
    char	*dst;
	if (x < 0 || y < 0 || x >= cub->s_width || y >= cub->s_height)
		return ;
	dst = cub->win.addr + (y * cub->win.ll + x * (cub->win.bpp / 8));
	*(unsigned int*)dst = color;
}

void	ray_correct(float *ray)
{
	while (*ray < 0.0f)
		*ray += 1.0f;
    while (*ray >= 1.0f)
		*ray -= 1.0f;
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
