/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 22:39:44 by levensta          #+#    #+#             */
/*   Updated: 2021/01/13 22:43:44 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	absf(float f)
{
	if (f < 0)
		f *= -1;
	return (f);
}

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

	int		x = 0;
	float	x1;
	float	y1;
	int		column_h;
	int		wall = 0;
	float 	a;
	float	b;


	float		dx;
	float		dy;
	float		ray;
	float		distance;
	//x and y start position
	distance = 0;
    ray = cub->plr.route - FOV/2;
	clear_image(cub);
	ray_correct(&ray);
    while (x < screenWidth)
    {
		wall = 0;
		x1 = cub->plr.x0;
		y1 = cub->plr.y0;
		ray_correct(&ray);
		// printf("-------_______-----\n");
		while (!wall)
		{
			// printf("%f\n", ray);
			// убрать dx, dy из структуры
			if (ray <= 0.5)
				dx = ceilf(x1 + EPS) - x1;
			else
				dx = x1 - floorf(x1 - EPS);
			if (ray >= 0.25 && ray < 0.75)
				dy = ceilf(y1 + EPS) - y1;
			else   
				dy = y1 - floorf(y1 - EPS);

			if ((ray >= 0.25 && ray < 0.5) || (ray >= 0.75 && ray < 1))
			{
				a = tanf(fmodf(ray, 0.25f) * 2 * M_PI) * dx;
				b = tanf(M_PI_2 - fmodf(ray, 0.25f) * 2 * M_PI) * dy;
			}
			else
			{
				a = tanf(M_PI_2 - fmodf(ray, 0.25f) * 2 * M_PI) * dx;
				b = tanf(fmodf(ray, 0.25f) * 2 * M_PI) * dy;
			}
			float c;
			float d;

			c = sqrtf(dx * dx + a * a);
			d = sqrtf(dy * dy + b * b);
			if (d < c)
			{
				if (ray <= 0.5)
					x1 += b;
				else
					x1 -= b;
				if (ray >= 0.25 && ray < 0.75)
					y1 = ceilf(y1 + EPS);
				else
					y1 = floorf(y1 - EPS);
			}
			else
			{
				if (ray <= 0.5)
					x1 = ceilf(x1 + EPS);
				else
					x1 = floorf(x1 - EPS);
				if (ray >= 0.25 && ray < 0.75)
					y1 += a;
				else
					y1 -= a;
			}


			if (x1 < 0 || y1 < 0 || y1 > mapHeight || x1 > mapWidth)
				wall = 1;
			if (x1 - floorf(x1) < EPS)
			{
				if (cub->worldMap[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS)] == '1')
					wall = 1;
				else if (cub->worldMap[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS) - 1] == '1')
					wall = 1;
			}
			if (y1 - floorf(y1) < EPS)
			{
				if (cub->worldMap[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS)] == '1')
					wall = 1;
				else if (cub->worldMap[(int)floorf(y1 + EPS) - 1][(int)floorf(x1 + EPS)] == '1')
					wall = 1;
			}

		}
		distance = sqrtf(powf(cub->plr.x0 - x1, 2) + powf(cub->plr.y0 - y1, 2));
		distance = distance * cosf(absf(cub->plr.route * 360.0f - ray * 360.0f) * (M_PI / 180.0f));

		column_h = screenHeight / 2;
        column_h = (float)column_h / tanf((FOV * 360.0f / 2.0f) * (M_PI / 180.0f));
        column_h = (int)ceilf((float)column_h / distance);

		int i = 0;
		i = (screenHeight - column_h) / 2;
		char *img = cub->win.addr;
		char *tex = cub->tex.addr;
		int	 j = 0;
		while(j < i){
			img += cub->win.line_length;
			j++;
		}
		int		h = 0;
		int		n = 0;
		int		res = cub->tex.height / column_h;
		while (i < (screenHeight + column_h) / 2)
		{
			// my_mlx_pixel_put(cub, x, i, 0xFF00FF);
			img[(x * 4)] = tex[(n * 4)];
			img[(x * 4) + 1] = tex[(n * 4) + 1];
			img[(x * 4) + 2] = tex[(n * 4) + 2];
			img += cub->win.line_length;
			if (res > 0 && h < cub->tex.height && (h % res) == 0)
				tex += cub->tex.line_length;
			if (i + 1 == screenHeight)
				break ;
			i++;
			h++;
		}
		// printf("%f\n", ray);
		ray += FOV / screenWidth;
		// printf("%f\n", ray);
		x++;
	}
	int tx;
	int ty;
	mlx_mouse_get_pos(cub->vars.win, &tx, &ty);
	// printf("x: %d, y: %d\n", tx, ty);
	// printf("route: %f\n", cub->plr.route);
	// printf("x: %f\n", cub->pl r.x0);
	// printf("y: %f\n", cub->plr.y0);
	mlx_put_image_to_window(cub->vars.mlx, cub->vars.win, cub->win.img, 0, 0);
	// mlx_put_image_to_window(cub->vars.mlx, cub->vars.win, cub->tex.img, 0, 0);
	return (0);
}