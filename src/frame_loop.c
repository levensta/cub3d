/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 22:39:44 by levensta          #+#    #+#             */
/*   Updated: 2020/12/27 23:11:43 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	frame_loop(t_all *cub)
{

	int worldMap[mapWidth][mapHeight]=
	{
	{1,1,1,1,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,1,1,1,1},
	};


	int		x = 0;
	int		wall = 0;
	cub->plr.x0 = 2.5;
	cub->plr.x0 = 2.5;  //x and y start position
	cub->plr.x1 = 0;
	cub->plr.y1 = 0;
	cub->distance = 0;
	cub->route = 0;
    cub->ray = cub->route - FOV/2;
	ray_correct(&cub->ray);
    while (x < screenWidth)
    {
		cub->plr.x1 = cub->plr.x0;
		cub->plr.y1 = cub->plr.y0;
		ray_correct(&cub->ray);
		while (!wall)
		{
			if (cub->ray <= 0.5)
				cub->dx = ceilf(cub->plr.x1) - cub->plr.x1;
			else
				cub->dx = cub->plr.x1 - floorf(cub->plr.x1 - EPS);
			if (cub->ray >= 0.25 && cub->ray < 0.75)
				cub->dy = ceilf(cub->plr.y1) - cub->plr.y1;
			else   
				cub->dy = cub->plr.y1 - floorf(cub->plr.y1 - EPS);

			float a = tanf(fmodf(cub->ray, 0.25f) * 2 * M_PI) * cub->dx;
			float b = tanf(M_PI_2 - fmodf(cub->ray, 0.25f) * 2 * M_PI) * cub->dy;
			if (b < a)
			{
				if (cub->ray <= 0.5)
					cub->plr.x1 += a;
				else
					cub->plr.x1 -= b;
				if (cub->ray >= 0.25 && cub->ray < 0.75)
					cub->plr.y1 = ceilf(cub->plr.y1);
				else
					cub->plr.y1 = floorf(cub->plr.y1);
			}
			else
			{
				if (cub->ray <= 0.5)
					cub->plr.x1 = ceilf(cub->plr.x1);
				else
					cub->plr.x1 = floorf(cub->plr.x1);
				if (cub->ray >= 0.25 && cub->ray < 0.75)
					cub->plr.y1 += a;
				else
					cub->plr.y1 -= a;
			}



			if (cub->ray >= 0.125 && cub->ray < 0.375)
			{
				if (worldMap[(int)ceilf(cub->plr.x1 + EPS)][(int)floor(cub->plr.y1 - EPS)] == 1)
					wall = 1;
			}

			if (cub->ray >= 0.375 && cub->ray < 0.625)
			{
				if (worldMap[(int)floorf(cub->plr.x1 - EPS)][(int)ceilf(cub->plr.y1 + EPS)] == 1)
					wall = 1;
			}

			if (cub->ray >= 0.625 && cub->ray < 0.875)
			{
				if (worldMap[(int)floor(cub->plr.x1 - EPS)][(int)floor(cub->plr.y1 - EPS)] == 1)
					wall = 1;
			}

			else
			{
				if (worldMap[(int)floor(cub->plr.x1 - EPS)][(int)floor(cub->plr.y1 - EPS)] == 1)
					wall = 1;
			}

		}
		cub->distance = sqrtf(powf(cub->plr.x0 - cub->plr.x1, 2) + powf(cub->plr.y0 - cub->plr.y1, 2));


		cub->column_h = screenHeight / 2;
        cub->column_h = (float)cub->column_h / tanf((FOV * 360.0f / 2.0f) * (M_PI / 180.0f));
        cub->column_h = (int)ceilf((float)cub->column_h / cub->distance);

		int i = 0;
		int j = 0;
		while (i < screenWidth)
		{
			j = (screenHeight - cub->column_h) / 2; 
			while (j < (screenHeight + cub->column_h) / 2)
			{
				my_mlx_pixel_put(cub, i, j, 0xFF00FF);
				j++;
			}
			i++;
		}
		cub->ray += FOV / screenWidth;
		x++;
	}
	return (0);
}