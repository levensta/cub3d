/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:31:59 by levensta          #+#    #+#             */
/*   Updated: 2021/02/16 21:22:21 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_hypot(t_all *cub, int flag, float a, float b)
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

static void	send_ray(t_all *cub)
{
	float	a;
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

static void	step_in_x(t_all *cub, char *wall, char *is_x)
{
	if (cub->scene.world_map[(int)floorf(cub->y1 + EPS)]\
	[(int)floorf(cub->x1 + EPS)] == '1')
		*wall = 1;
	else if (cub->scene.world_map[(int)floorf(cub->y1 + EPS)]\
	[(int)floorf(cub->x1 + EPS) - 1] == '1')
		*wall = 1;
	if (cub->scene.world_map[(int)floorf(cub->y1 + EPS)]\
	[(int)floorf(cub->x1 + EPS)] == '2')
		find_sprite(cub, (int)floorf(cub->x1 + EPS), \
		(int)floorf(cub->y1 + EPS));
	if (cub->scene.world_map[(int)floorf(cub->y1 + EPS)]\
	[(int)floorf(cub->x1 + EPS) - 1] == '2')
		find_sprite(cub, (int)floorf(cub->x1 + EPS) - 1, \
		(int)floorf(cub->y1 + EPS));
	*is_x = 1;
}

static void	step_in_y(t_all *cub, char *wall, char *is_x)
{
	if (cub->scene.world_map[(int)floorf(cub->y1 + EPS)]\
	[(int)floorf(cub->x1 + EPS)] == '1')
		*wall = 1;
	else if (cub->scene.world_map[(int)floorf(cub->y1 + EPS) - 1]\
	[(int)floorf(cub->x1 + EPS)] == '1')
		*wall = 1;
	if (cub->scene.world_map[(int)floorf(cub->y1 + EPS)]\
	[(int)floorf(cub->x1 + EPS)] == '2')
		find_sprite(cub, (int)floorf(cub->x1 + EPS), \
		(int)floorf(cub->y1 + EPS));
	if (cub->scene.world_map[(int)floorf(cub->y1 + EPS) - 1]\
	[(int)floorf(cub->x1 + EPS)] == '2')
		find_sprite(cub, (int)floorf(cub->x1 + EPS), \
		(int)floorf(cub->y1 + EPS) - 1);
	*is_x = 0;
}

void		raycasting(t_all *cub, char *is_x)
{
	char	wall;
	int		i;

	wall = 0;
	i = 0;
	while (!wall)
	{
		send_ray(cub);
		if (cub->x1 < 0 || cub->y1 < 0 || cub->y1 >= cub->scene.map_height || \
		cub->x1 >= ft_strlen(cub->scene.world_map[(int)floorf(cub->y1)]))
			wall = 1;
		if (cub->x1 - floorf(cub->x1) < EPS)
			step_in_x(cub, &wall, is_x);
		if (cub->y1 - floorf(cub->y1) < EPS)
			step_in_y(cub, &wall, is_x);
	}
}
