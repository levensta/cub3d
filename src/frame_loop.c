/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 22:39:44 by levensta          #+#    #+#             */
/*   Updated: 2021/01/31 21:15:16 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int		map_width(char *map)
// {
// 	int x;
// 	int i;

// 	x = 0;
// 	i = 0;
// 	while(map[i])
// 	{
// 		if (ft_memchr("10NWSE2", map[i], 7))
// 			x++;
// 		i++;
// 	}
// 	return (x);
// }

int	frame_loop(t_all *cub)
{

	cub->x = 0;
	float	x1;
	float	y1;
	char	wall = 0;
	float 	a;
	float	b;

	char	is_x = 0;


	float		dx;
	float		dy;
    cub->ray = cub->plr.route - FOV/2;
	// clear_image(cub);
	ray_correct(&cub->ray);
	// printf("%f\n", cub->plr.route);
    while (cub->x < cub->scene.screen_width)
    {
		cub->num_spr = 0;
		wall = 0;
		x1 = cub->plr.x0;
		y1 = cub->plr.y0;
		ray_correct(&cub->ray);
		while (!wall)
		{
			if (cub->ray <= 0.5)
				dx = ceilf(x1 + EPS) - x1;
			else
				dx = x1 - floorf(x1 - EPS);
			if (cub->ray >= 0.25 && cub->ray < 0.75)
				dy = ceilf(y1 + EPS) - y1;
			else   
				dy = y1 - floorf(y1 - EPS);

			if ((cub->ray >= 0.25 && cub->ray < 0.5) || (cub->ray >= 0.75 && cub->ray < 1))
			{
				a = tanf(fmodf(cub->ray, 0.25f) * 2 * M_PI) * dx;
				b = tanf(M_PI_2 - fmodf(cub->ray, 0.25f) * 2 * M_PI) * dy;
			}
			else
			{
				a = tanf(M_PI_2 - fmodf(cub->ray, 0.25f) * 2 * M_PI) * dx;
				b = tanf(fmodf(cub->ray, 0.25f) * 2 * M_PI) * dy;
			}
			// float c;
			// float d;

			// c = sqrtf(dx * dx + a * a);
			// d = sqrtf(dy * dy + b * b);
			// float c1;
			// float d1;

			// c1 = hypotf(dx, a);
			// d1 = hypotf(dy, b);
			if (hypotf(dy, b) < hypotf(dx, a))
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


			if (x1 < 0 || y1 < 0 || y1 >= cub->scene.map_height || \
			x1 >= ft_strlen(cub->scene.world_map[(int)floorf(y1)]))
				wall = 1;
			if (x1 - floorf(x1) < EPS)
			{
				if (cub->scene.world_map[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS)] == '1')
					wall = 1;
				else if (cub->scene.world_map[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS) - 1] == '1')
					wall = 1;
				if (cub->scene.world_map[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS)] == '2')
					find_sprite(cub, (int)floorf(x1 + EPS), (int)floorf(y1 + EPS));
				else if (cub->scene.world_map[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS) - 1] == '2')
					find_sprite(cub, (int)floorf(x1 + EPS) - 1, (int)floorf(y1 + EPS));
				is_x = 1;
			}
			else if (y1 - floorf(y1) < EPS)
			{
				if (cub->scene.world_map[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS)] == '1')
					wall = 1;
				else if (cub->scene.world_map[(int)floorf(y1 + EPS) - 1][(int)floorf(x1 + EPS)] == '1')
					wall = 1;
				if (cub->scene.world_map[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS)] == '2')
					find_sprite(cub, (int)floorf(x1 + EPS), (int)floorf(y1 + EPS));
				else if (cub->scene.world_map[(int)floorf(y1 + EPS) - 1][(int)floorf(x1 + EPS)] == '2')
					find_sprite(cub, (int)floorf(x1 + EPS), (int)floorf(y1 + EPS) - 1);
				is_x = 0;
			}

		}
//
		cub->column_h = count_column(cub->plr.x0 - x1, \
		cub->plr.y0 - y1, cub);
		if (is_x)
		{
			if (cub->ray >= 0 && cub->ray < 0.5f) // east
				draw_texture(cub, y1 - floorf(y1), cub->column_h, 2);
			else
				draw_texture(cub, ceilf(y1) - y1, cub->column_h, 3); // west
		}
		else
		{
			if (cub->ray >= 0.25f && cub->ray < 0.75f) // south
				draw_texture(cub, ceilf(x1) - x1, cub->column_h, 0);
			else // north
				draw_texture(cub, x1 - floorf(x1), cub->column_h, 1);
		}
		draw_ceil(cub, cub->column_h);
		draw_floor(cub, cub->column_h);
		int w = 0;
		find_dists(cub);
		sort_sprites(cub);

		while (w < cub->num_spr)
		{
			// printf("%f, %f\n", cub->sprite[w].x, cub->sprite[w].y);
			draw_sprite(cub, cub->sprite[w], x1, y1);
			// cub->sprite[w].x = 0;
			// cub->sprite[w].y = 0;
			// cub->sprite[w].distance = 0;
			w++;
		}

		cub->ray += FOV / cub->scene.screen_width;
		cub->x++;
	}
	mlx_put_image_to_window(cub->vars.mlx, cub->vars.win, cub->win.img, 0, 0);
	return (0);
}
 