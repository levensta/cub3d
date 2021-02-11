/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 22:39:44 by levensta          #+#    #+#             */
/*   Updated: 2021/02/11 23:24:10 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_hypot(t_all *cub, int flag, float a, float b)
{
	if (flag)
	{
		if (cub->ray <= 0.5)
			cub->x1 += b;
		else
			cub->x1 -= b;
		if (cub->ray >= 0.25 && cub->ray < 0.75)
			cub->y1 = ceilf(cub->y1 + EPS);
		else
			cub->y1 = floorf(cub->y1 - EPS);
	}
	else
	{
		if (cub->ray <= 0.5)
			cub->x1 = ceilf(cub->x1 + EPS);
		else
			cub->x1 = floorf(cub->x1 - EPS);
		if (cub->ray >= 0.25 && cub->ray < 0.75)
			cub->y1 += a;
		else
			cub->y1 -= a;
	}
}

void	send_ray(t_all *cub)
{
	float 	a;
	float	b;
	float	dx;
	float	dy;
	
	if (cub->ray <= 0.5)
		dx = ceilf(cub->x1 + EPS) - cub->x1;
	else
		dx = cub->x1 - floorf(cub->x1 - EPS);
	if (cub->ray >= 0.25 && cub->ray < 0.75)
		dy = ceilf(cub->y1 + EPS) - cub->y1;
	else   
		dy = cub->y1 - floorf(cub->y1 - EPS);
	if ((cub->ray >= 0.25 && cub->ray < 0.5) \
	|| (cub->ray >= 0.75 && cub->ray < 1))
	{
		a = tanf(fmodf(cub->ray, 0.25f) * 2 * M_PI) * dx;
		b = tanf(M_PI_2 - fmodf(cub->ray, 0.25f) * 2 * M_PI) * dy;
	}
	else
	{
		a = tanf(M_PI_2 - fmodf(cub->ray, 0.25f) * 2 * M_PI) * dx;
		b = tanf(fmodf(cub->ray, 0.25f) * 2 * M_PI) * dy;
	}
	check_hypot(cub, (hypotf(dy, b) < hypotf(dx, a)), a, b);
}

void	step_in_x(t_all *cub, char *wall, char *is_x)
{
	if (cub->scene.world_map[(int)floorf(cub->y1 + EPS)] \
	[(int)floorf(cub->x1 + EPS)] == '1')
		*wall = 1;
	else if (cub->scene.world_map[(int)floorf(cub->y1 + EPS)] \
	[(int)floorf(cub->x1 + EPS) - 1] == '1')
		*wall = 1;
	if (cub->scene.world_map[(int)floorf(cub->y1 + EPS)] \
	[(int)floorf(cub->x1 + EPS)] == '2')
		find_sprite(cub, (int)floorf(cub->x1 + EPS), \
		(int)floorf(cub->y1 + EPS));
	else if (cub->scene.world_map[(int)floorf(cub->y1 + EPS)] \
	[(int)floorf(cub->x1 + EPS) - 1] == '2')
		find_sprite(cub, (int)floorf(cub->x1 + EPS) - 1, \
		(int)floorf(cub->y1 + EPS));
	*is_x = 1;
}

void	step_in_y(t_all *cub, char *wall, char *is_x)
{
	if (cub->scene.world_map[(int)floorf(cub->y1 + EPS)] \
	[(int)floorf(cub->x1 + EPS)] == '1')
		*wall = 1;
	else if (cub->scene.world_map[(int)floorf(cub->y1 + EPS) - 1] \
	[(int)floorf(cub->x1 + EPS)] == '1')
		*wall = 1;
	if (cub->scene.world_map[(int)floorf(cub->y1 + EPS)] \
	[(int)floorf(cub->x1 + EPS)] == '2')
		find_sprite(cub, (int)floorf(cub->x1 + EPS), \
		(int)floorf(cub->y1 + EPS));
	else if (cub->scene.world_map[(int)floorf(cub->y1 + EPS) - 1] \
	[(int)floorf(cub->x1 + EPS)] == '2')
		find_sprite(cub, (int)floorf(cub->x1 + EPS), \
		(int)floorf(cub->y1 + EPS) - 1);
	*is_x = 0;
}

void	drawing_room(t_all *cub, char is_x)
{
	cub->column_h = count_column(cub->plr.x0 - cub->x1, \
	cub->plr.y0 - cub->y1, cub);
	if (is_x)
	{
		if (cub->ray >= 0 && cub->ray < 0.5f)
			draw_texture(cub, cub->y1 - floorf(cub->y1), cub->column_h, 2);
		else
			draw_texture(cub, ceilf(cub->y1) - cub->y1, cub->column_h, 3);
	}
	else
	{
		if (cub->ray >= 0.25f && cub->ray < 0.75f)
			draw_texture(cub, ceilf(cub->x1) - cub->x1, cub->column_h, 0);
		else
			draw_texture(cub, cub->x1 - floorf(cub->x1), cub->column_h, 1);
	}
	draw_ceil(cub, cub->column_h);
	draw_floor(cub, cub->column_h);
}

int	frame_loop(t_all *cub)
{
	char	wall;
	char	is_x;

	wall = 0;
	is_x = 0;
	cub->x = 0;
    cub->ray = cub->plr.route - FOV/2;
	ray_correct(&cub->ray);
	cub->num_spr = 0;
    while (cub->x < cub->s_width)
    {
		wall = 0;
		cub->x1 = cub->plr.x0;
		cub->y1 = cub->plr.y0;
		ray_correct(&cub->ray);
		while (!wall)
		{
			send_ray(cub);
			if (cub->x1 < 0 || cub->y1 < 0 || cub->y1 >= cub->scene.map_height || \
			cub->x1 >= ft_strlen(cub->scene.world_map[(int)floorf(cub->y1)]))
				wall = 1;
			if (cub->x1 - floorf(cub->x1) < EPS)
				step_in_x(cub, &wall, &is_x);
			else if (cub->y1 - floorf(cub->y1) < EPS)
				step_in_y(cub, &wall, &is_x);
		}
		drawing_room(cub, is_x);
		cub->ray += FOV / cub->s_width;
		cub->x++;
	}
	find_dists(cub);
	sort_sprites(cub);
	int w = 0;
	while (w < cub->num_spr)
	{
		draw_sprite(cub, cub->sprite[w]);
		w++;
	}
	mlx_put_image_to_window(cub->vars.mlx, cub->vars.win, cub->win.img, 0, 0);
	return (0);
}
 