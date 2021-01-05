/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 22:39:44 by levensta          #+#    #+#             */
/*   Updated: 2021/01/05 02:22:18 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    clear_image(t_all *cub)
{
    int x;
    int y;
    x = -1;
    while (++x < screenWidth)
    {
        y = -1;
        while (++y < screenHeight)
            my_mlx_pixel_put(cub, x, y, 0);
    }
}

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
	float	x1;
	float	y1;
	int		column_h;
	int		wall = 0;
	//x and y start position
	cub->distance = 0;
    cub->ray = cub->plr.route - FOV/2;
	clear_image(cub);
	ray_correct(&cub->ray);
    while (x < screenWidth)
    {
		wall = 0;
		x1 = cub->plr.x0;
		y1 = cub->plr.y0;
		ray_correct(&cub->ray);
		// printf("-------_______-----\n");
		while (!wall)
		{
			// printf("%f\n", cub->ray);
			if (cub->ray <= 0.5)
				cub->dx = ceilf(x1) - x1;
			else
				cub->dx = x1 - floorf(x1 - EPS);
			if (cub->ray >= 0.25 && cub->ray < 0.75)
				cub->dy = ceilf(y1) - y1;
			else   
				cub->dy = y1 - floorf(y1 - EPS);

			float a = tanf(fmodf(cub->ray, 0.25f) * 2 * M_PI) * cub->dx;
			float b = tanf(M_PI_2 - fmodf(cub->ray, 0.25f) * 2 * M_PI) * cub->dy;
			if (b < a)
			{
				if (cub->ray <= 0.5)
					x1 += b;
				else
					x1 -= b;
				if (cub->ray >= 0.25 && cub->ray < 0.75)
					y1 = ceilf(y1 + EPS);
				else
					y1 = floorf(y1 - EPS);
			}
			else
			{
				if (cub->ray <= 0.5)
					x1 = ceilf(x1 + EPS);
				else
					x1 = floorf(x1 - EPS);
				if (cub->ray >= 0.25 && cub->ray < 0.75)
					y1 += a;
				else
					y1 -= a;
			}


			if (x1 < 0 || y1 < 0 || y1 >= mapHeight || x1 >= mapWidth)
				wall = 1;
			if (x1 - floorf(x1) < EPS)
			{
				if (worldMap[(int)floorf(y1)][(int)floorf(x1)] == 1)
					wall = 1;
				else if (worldMap[(int)floorf(y1)][(int)floorf(x1 - 1)] == 1)
					wall = 1;
				// printf("x: %f, y: %f, wall: %d, ray: %f, a: %f, b: %f\n", x1, y1, wall, cub->ray, a, b);
				if (cub->ray > 0.999998)
					exit(1);
			}
			if (y1 - floorf(y1) < EPS)
			{
				if (worldMap[(int)floorf(y1)][(int)floorf(x1)] == 1)
					wall = 1;
				else if (worldMap[(int)floorf(y1 - 1)][(int)floorf(x1)] == 1)
					wall = 1;
				// printf("x: %f, y: %f, wall: %d, ray: %f, a: %f, b: %f\n", x1, y1, wall, cub->ray, a, b);
				// if (cub->ray > 0.999998)
				// 	exit(0);
			}
			// if (cub->ray >= 0.125 && cub->ray < 0.375)
			// {
			// 	if (worldMap[(int)ceilf(x1 + EPS)][(int)floor(y1 - EPS)] == 1)
			// 		wall = 1;
			// }

			// else if (cub->ray >= 0.375 && cub->ray < 0.625)
			// {
			// 	if (worldMap[(int)floorf(x1 - EPS)][(int)ceilf(y1 + EPS)] == 1)
			// 		wall = 1;
			// }

			// else if (cub->ray >= 0.625 && cub->ray < 0.875)
			// {
			// 	if (worldMap[(int)floor(x1 - EPS)][(int)floor(y1 - EPS)] == 1)
			// 		wall = 1;
			// }

			// else
			// {
			// 	if (worldMap[(int)floor(x1 - EPS)][(int)floor(y1 - EPS)] == 1)
			// 		wall = 1;
			// }

		}
		cub->distance = sqrtf(powf(cub->plr.x0 - x1, 2) + powf(cub->plr.y0 - y1, 2));

		column_h = screenHeight / 2;
        column_h = (float)column_h / tanf((FOV * 360.0f / 2.0f) * (M_PI / 180.0f));
        column_h = (int)ceilf((float)column_h / cub->distance);

		int i = 0;
		int j = 0;
		while (i < screenWidth)
		{
			j = (screenHeight - column_h) / 2; 
			while (j < (screenHeight + column_h) / 2)
			{
				my_mlx_pixel_put(cub, i, j, 0xFF00FF);
				j++;
			}
			i++;
		}
		// printf("%f\n", cub->ray);
		cub->ray += FOV / screenWidth;
		// printf("%f\n", cub->ray);
		x++;
	}
	mlx_put_image_to_window(cub->vars.mlx, cub->vars.win, cub->win.img, 0, 0);
	return (0);
}