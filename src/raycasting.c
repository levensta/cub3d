/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:31:59 by levensta          #+#    #+#             */
/*   Updated: 2021/02/24 21:20:21 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_hypot(t_all *cub, int flag, double a, double b)
{
	if (flag)
	{
		if (cub->ray <= 0.5)
			cub->x1 += b;
		else
			cub->x1 -= b;
		if (cub->ray >= 0.25 && cub->ray < 0.75)
			cub->y1 = ceil(cub->y1 + EPS);
		else
			cub->y1 = floor(cub->y1 - EPS);
	}
	else
	{
		if (cub->ray <= 0.5)
			cub->x1 = ceil(cub->x1 + EPS);
		else
			cub->x1 = floor(cub->x1 - EPS);
		if (cub->ray >= 0.25 && cub->ray < 0.75)
			cub->y1 += a;
		else
			cub->y1 -= a;
	}
}

static void	send_ray(t_all *cub)
{
	double	a;
	double	b;
	double	dx;
	double	dy;

	if (cub->ray <= 0.5)
		dx = ceil(cub->x1 + EPS) - cub->x1;
	else
		dx = cub->x1 - floor(cub->x1 - EPS);
	if (cub->ray >= 0.25 && cub->ray < 0.75)
		dy = ceil(cub->y1 + EPS) - cub->y1;
	else
		dy = cub->y1 - floor(cub->y1 - EPS);
	if ((cub->ray >= 0.25 && cub->ray < 0.5) \
	|| (cub->ray >= 0.75 && cub->ray < 1))
	{
		a = tan(fmod(cub->ray, 0.25f) * 2 * M_PI) * dx;
		b = tan(M_PI_2 - fmod(cub->ray, 0.25f) * 2 * M_PI) * dy;
	}
	else
	{
		a = tan(M_PI_2 - fmod(cub->ray, 0.25f) * 2 * M_PI) * dx;
		b = tan(fmod(cub->ray, 0.25f) * 2 * M_PI) * dy;
	}
	check_hypot(cub, (hypot(dy, b) < hypot(dx, a)), a, b);
}

static void	step_in_x(t_all *cub, char *wall, char *is_x)
{
	if (cub->scene.world_map[(int)floor(cub->y1 + EPS)]\
	[(int)floor(cub->x1 + EPS)] == '1')
		*wall = 1;
	else if (cub->scene.world_map[(int)floor(cub->y1 + EPS)]\
	[(int)floor(cub->x1 + EPS) - 1] == '1')
		*wall = 1;
	if (cub->scene.world_map[(int)floor(cub->y1 + EPS)]\
	[(int)floor(cub->x1 + EPS)] == '2')
		find_sprite(cub, (int)floor(cub->x1 + EPS), \
		(int)floor(cub->y1 + EPS));
	if (cub->scene.world_map[(int)floor(cub->y1 + EPS)]\
	[(int)floor(cub->x1 + EPS) - 1] == '2')
		find_sprite(cub, (int)floor(cub->x1 + EPS) - 1, \
		(int)floor(cub->y1 + EPS));
	*is_x = 1;
}

static void	step_in_y(t_all *cub, char *wall, char *is_x)
{
	if (cub->scene.world_map[(int)floor(cub->y1 + EPS)]\
	[(int)floor(cub->x1 + EPS)] == '1')
		*wall = 1;
	else if (cub->scene.world_map[(int)floor(cub->y1 + EPS) - 1]\
	[(int)floor(cub->x1 + EPS)] == '1')
		*wall = 1;
	if (cub->scene.world_map[(int)floor(cub->y1 + EPS)]\
	[(int)floor(cub->x1 + EPS)] == '2')
		find_sprite(cub, (int)floor(cub->x1 + EPS), \
		(int)floor(cub->y1 + EPS));
	if (cub->scene.world_map[(int)floor(cub->y1 + EPS) - 1]\
	[(int)floor(cub->x1 + EPS)] == '2')
		find_sprite(cub, (int)floor(cub->x1 + EPS), \
		(int)floor(cub->y1 + EPS) - 1);
	*is_x = 0;
}

void		raycasting(t_all *cub, char *is_x)
{
	char	wall;

	wall = 0;
	while (!wall)
	{
		send_ray(cub);
		if (cub->x1 < 0 || cub->y1 < 0 || cub->y1 >= cub->scene.map_height || \
		cub->x1 >= ft_strlen(cub->scene.world_map[(int)floor(cub->y1)]))
			wall = 1;
		if (cub->x1 - floor(cub->x1) < EPS)
			step_in_x(cub, &wall, is_x);
		if (cub->y1 - floor(cub->y1) < EPS)
			step_in_y(cub, &wall, is_x);
	}
}
