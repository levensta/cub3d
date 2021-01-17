/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 22:39:44 by levensta          #+#    #+#             */
/*   Updated: 2021/01/17 22:35:07 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_column(float x, float y, float route, float ray)
{
	float	distance;
	int		column_h;
	
	distance = 0;
	distance = sqrtf(powf(x, 2) + powf(y, 2));
	distance = distance * cosf(fabs(route * 360.0f - ray * 360.0f) * (M_PI / 180.0f));

	column_h = screenHeight / 2;
	column_h = (float)column_h / tanf((FOV * 360.0f / 2.0f) * (M_PI / 180.0f));
	column_h = (int)ceilf((float)column_h / distance);
	return (column_h);
}

void	draw_ceil(t_all *cub, int x, int column_h)
{
		int		color;
		float	j;
		int i;

		i = (screenHeight - column_h) / 2;
		color = 0x1E91D6;
		j = -1;
		while (j++ < i)
			my_mlx_pixel_put(cub, x, j, color);
}

void	draw_texture_no(t_all *cub, int x, int column_h, float hit)
{
	unsigned int	color;
	float			j;
	int				i;

	i = (screenHeight - column_h) / 2;
	j = 0;
	hit *= cub->txt[0].width;
	while (i < (screenHeight + column_h) / 2)
	{
		color = *(unsigned int*)(cub->txt[0].addr + ((int)j * cub->txt[0].line_length + (int)hit * (cub->txt[0].bits_per_pixel / 8)));
		my_mlx_pixel_put(cub, x, i, color);
		i++;
		j += (float)cub->txt[0].height / (float)column_h;
	}
}

void	draw_texture_so(t_all *cub, int x, int column_h, float hit)
{
	unsigned int	color;
	float			j;
	int				i;

	i = (screenHeight - column_h) / 2;
	j = 0;
	hit *= cub->txt[1].width;
	while (i < (screenHeight + column_h) / 2)
	{
		color = *(unsigned int*)(cub->txt[1].addr + ((int)j * cub->txt[1].line_length + (int)hit * (cub->txt[1].bits_per_pixel / 8)));
		my_mlx_pixel_put(cub, x, i, color);
		i++;
		j += (float)cub->txt[1].height / (float)column_h;
	}
}

void	draw_texture_we(t_all *cub, int x, int column_h, float hit)
{
	unsigned int	color;
	float			j;
	int				i;

	i = (screenHeight - column_h) / 2;
	j = 0;
	hit *= cub->txt[2].width;
	while (i < (screenHeight + column_h) / 2)
	{
		color = *(unsigned int*)(cub->txt[2].addr + ((int)j * cub->txt[2].line_length + (int)hit * (cub->txt[2].bits_per_pixel / 8)));
		my_mlx_pixel_put(cub, x, i, color);
		i++;
		j += (float)cub->txt[2].height / (float)column_h;
	}
}

void	draw_texture_ea(t_all *cub, int x, int column_h, float hit)
{
	unsigned int	color;
	float			j;
	int				i;

	i = (screenHeight - column_h) / 2;
	j = 0;
	hit *= cub->txt[3].width;
	while (i < (screenHeight + column_h) / 2)
	{
		color = *(unsigned int*)(cub->txt[3].addr + ((int)j * cub->txt[3].line_length + (int)hit * (cub->txt[3].bits_per_pixel / 8)));
		my_mlx_pixel_put(cub, x, i, color);
		i++;
		j += (float)cub->txt[3].height / (float)column_h;
	}
}

void	draw_floor(t_all *cub, int x, int column_h)
{
	int j;
	int color;

	j = (screenHeight + column_h) / 2 - 1;
	color = 0x4CB963;
	while (j++ < screenHeight)
		my_mlx_pixel_put(cub, x, j, color);
}

float	absf(float f)
{
	if (f < 0)
		f *= -1;
	return (f);
}

void	clear_image(t_all *cub)
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

	char	is_x = 0;


	float		dx;
	float		dy;
	float		ray;
	//x and y start position
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
				is_x = 1;
			}
			if (y1 - floorf(y1) < EPS)
			{
				if (cub->worldMap[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS)] == '1')
					wall = 1;
				else if (cub->worldMap[(int)floorf(y1 + EPS) - 1][(int)floorf(x1 + EPS)] == '1')
					wall = 1;
				is_x = 0;
			}

		}
//
		// float			hit;
		// unsigned int	color;
		char			is_west = 0;
		char			is_north = 0;
		if (is_x)
		{
			if (ray >= 0 && ray < 0.5f) // west
			{
				draw_texture_we(cub, x, column_h, y1 - floorf(y1));
				// hit = y1 - floorf(y1);
				is_west = 1;
			}
			else
			{
				draw_texture_ea(cub, x, column_h, ceilf(y1) - y1);
				// hit = ceilf(y1) - y1; // east
				is_west = 0;
			}
		}
		else
		{
			if (ray >= 0.25f && ray < 0.75f) // north
			{
				draw_texture_no(cub, x, column_h, ceilf(x1) - x1);
				// hit = ceilf(x1) - x1;
				is_north = 1;
			}
			else // south
			{
				draw_texture_so(cub, x, column_h, x1 - floorf(x1));
				// hit = x1 - floorf(x1);
				is_north = 0;
			}
		}

		column_h = count_column(cub->plr.x0 - x1, \
		cub->plr.y0 - y1, cub->plr.route, ray);

		draw_ceil(cub, x, column_h);
		// hit *= cub->txt[].width;
		draw_floor(cub, x, column_h);

//
		// printf("%f\n", ray);
		ray += FOV / screenWidth;
		// printf("%f\n", ray);
		x++;
	}
	// int tx;
	// int ty;
	// mlx_mouse_get_pos(cub->vars.win, &tx, &ty);

	// printf("x: %d, y: %d\n", tx, ty);
	// printf("route: %f\n", cub->plr.route);
	// printf("x: %f\n", cub->pl r.x0);
	// printf("y: %f\n", cub->plr.y0);
	mlx_put_image_to_window(cub->vars.mlx, cub->vars.win, cub->win.img, 0, 0);
	// mlx_put_image_to_window(cub->vars.mlx, cub->vars.win, cub->tex.img, 0, 0);
	return (0);
}