/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 22:39:44 by levensta          #+#    #+#             */
/*   Updated: 2021/01/24 04:46:28 by levensta         ###   ########.fr       */
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

float	absf(float f)
{
	if (f < 0)
		f *= -1;
	return (f);
}

float	count_distance(float x, float y, float route, float ray)
{
	float distance;

	distance = sqrtf(powf(x, 2) + powf(y, 2));
	distance = distance * cosf(absf(route * 360.0f - ray * 360.0f) * (M_PI / 180.0f));
	return (distance);
}

int	count_column(float x, float y, t_all *cub)
{
	float	distance;
	int		column_h;
	
	distance = count_distance(x, y, cub->plr.route, cub->ray);
	column_h = cub->scene.screen_height / 2;
	column_h = (float)column_h / tanf((FOV * 360.0f / 2.0f) * (M_PI / 180.0f));
	column_h = (int)ceilf((float)column_h / distance);
	return (column_h);
}

void	draw_ceil(t_all *cub, int x, int column_h)
{
		float	j;
		int i;

		if (column_h < 0)
			column_h = 0;
		i = (cub->scene.screen_height - column_h) / 2;
		j = -1;
		while (j++ < i)
			my_mlx_pixel_put(cub, x, j, cub->scene.ceiling);
}

void	draw_texture(t_all *cub, int x, float hit, int n)
{
	unsigned int	color;
	float			j;
	int				i;
	int				max;

	i = (cub->scene.screen_height - cub->column_h) / 2;
	j = 0;
	max = (cub->scene.screen_height + cub->column_h) / 2;
	if (i < 0)
	{
		j = ((float)cub->txt[n].height / (float)cub->column_h) * (-i);
		i = 0;
		max = cub->scene.screen_height;
	}
	hit *= cub->txt[n].width;
	while (i < max)
	{
		color = *(unsigned int*)(cub->txt[n].addr + ((int)j * cub->txt[n].line_length + (int)hit * (cub->txt[n].bits_per_pixel / 8)));
		my_mlx_pixel_put(cub, x, i, color);
		i++;
		j += (float)cub->txt[n].height / (float)cub->column_h;
	}
}

void	draw_sprite(t_all *cub, int x, float hit, int n)
{
	unsigned int	color;
	float			j;
	int				i;
	int				max;

	i = (cub->scene.screen_height - cub->column_h) / 2;
	j = 0;
	max = (cub->scene.screen_height + cub->column_h) / 2;
	if (i < 0)
	{
		j = ((float)cub->txt[n].height / (float)cub->column_h) * (-i);
		i = 0;
		max = cub->scene.screen_height;
	}
	hit *= cub->txt[n].width;
	while (i < max)
	{
		color = *(unsigned int*)(cub->txt[n].addr + ((int)j * cub->txt[n].line_length + (int)hit * (cub->txt[n].bits_per_pixel / 8)));
		my_mlx_pixel_put(cub, x, i, color);
		i++;
		j += (float)cub->txt[n].height / (float)cub->column_h;
	}
}

void	draw_floor(t_all *cub, int x, int column_h)
{
	int j;

	if (column_h < 0)
		column_h = 0;
	j = (cub->scene.screen_height + column_h) / 2 - 1;
	while (j++ < cub->scene.screen_height)
		my_mlx_pixel_put(cub, x, j, cub->scene.flooring);
}

void	clear_image(t_all *cub)
{
	int x;
	int y;
	x = -1;
	while (++x < cub->scene.screen_width)
	{
		y = -1;
		while (++y < cub->scene.screen_height)
			my_mlx_pixel_put(cub, x, y, 0);
	}
}

int		find_repeat_spr(t_all *cub, int x1, int y1, char side)
{
	int i;

	i = 0;
	if (side == 'W')
		x1 -= 1;
	if (side == 'S')
		y1 -= 1;
	while (i < cub->num_spr)
	{
		if (cub->sprite[i].x == x1 && cub->sprite[i].y == y1)
			return (1);
		i++;
	}
	return (0);
}

void	sort_sprites(t_all *cub)
{
	t_sprite tmp;
	int		i;
	int		j;
	char	flag;

	i = 0;
	while (i < cub->num_spr)
	{
		flag = 1;
		j = 0;
		while (j < cub->num_spr - (i + 1))
		{
			if (cub->sprite[j].distance < cub->sprite[j + 1].distance)
			{
				flag = 0;
				tmp = cub->sprite[j];
				cub->sprite[j] = cub->sprite[j + 1];
				cub->sprite[j + 1] = tmp;
			}
			j++;
		}
		if (flag)
			break;
		i++;
	}
}
void	find_sprite(t_all *cub, float x1, float y1, char side)
{
	int i;

	i = 0;
	if (find_repeat_spr(cub, (int)floorf(x1), (int)floorf(y1), side))
		return ;
	cub->sprite[cub->num_spr].x = (int)floorf(x1);
	cub->sprite[cub->num_spr].y = (int)floorf(y1);
	if (side == 'W')
		cub->sprite[cub->num_spr].x -= 1;
	if (side == 'S')
		cub->sprite[cub->num_spr].y -= 1;
	cub->sprite[cub->num_spr].distance = count_distance(cub->plr.x0 - x1, cub->plr.y0 - y1, cub->plr.route, cub->ray);
	cub->num_spr++;
	sort_sprites(cub);
	while(i < cub->num_spr)
	{
		draw_sprite(cub, x, );
		i++;
	}
}

int	frame_loop(t_all *cub)
{

	int		x = 0;
	float	x1;
	float	y1;
	char	wall = 0;
	float 	a;
	float	b;

	char	is_x = 0;


	float		dx;
	float		dy;
    cub->ray = cub->plr.route - FOV/2;
	clear_image(cub);
	ray_correct(&cub->ray);
	int		i;
	i = 0;
	while (i < cub->num_spr)
	{
		cub->sprite[i].x = 0;
		cub->sprite[i].y = 0;
		cub->sprite[i].distance = 0;
		i++;
	}
	cub->num_spr = 0;
    while (x < cub->scene.screen_width)
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
			float c;
			float d;

			c = sqrtf(dx * dx + a * a);
			d = sqrtf(dy * dy + b * b);
			if (d < c)
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


			if (x1 < 0 || y1 < 0 || y1 > mapHeight || x1 > mapWidth)
			// || y1 > cub->scene.map_height || x1 > map_width(cub->scene.world_map[(int)floorf(y1)])
				wall = 1;
			if (x1 - floorf(x1) < EPS)
			{
				if (cub->scene.world_map[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS)] == '1')
					wall = 1;
				else if (cub->scene.world_map[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS) - 1] == '1')
					wall = 1;
				if (cub->scene.world_map[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS)] == '2')
					find_sprite(cub, x1, y1, 0);
				if (cub->scene.world_map[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS) - 1] == '2')
					find_sprite(cub, x1, y1, 'W');
				is_x = 1;
			}
			if (y1 - floorf(y1) < EPS)
			{
				if (cub->scene.world_map[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS)] == '1')
					wall = 1;
				else if (cub->scene.world_map[(int)floorf(y1 + EPS) - 1][(int)floorf(x1 + EPS)] == '1')
					wall = 1;
				if (cub->scene.world_map[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS)] == '2')
					find_sprite(cub, x1, y1, 0);
				if (cub->scene.world_map[(int)floorf(y1 + EPS) - 1][(int)floorf(x1 + EPS)] == '2')
					find_sprite(cub, x1, y1, 'S');
				is_x = 0;
			}

		}
//
		cub->column_h = count_column(cub->plr.x0 - x1, \
		cub->plr.y0 - y1, cub);
		if (is_x)
		{
			if (cub->ray >= 0 && cub->ray < 0.5f) // east
				draw_texture(cub, x, y1 - floorf(y1), 3);
			else
				draw_texture(cub, x, ceilf(y1) - y1, 2); // west
		}
		else
		{
			if (cub->ray >= 0.25f && cub->ray < 0.75f) // south
				draw_texture(cub, x, ceilf(x1) - x1, 1);
			else // north
				draw_texture(cub, x, x1 - floorf(x1), 0);
		}
		draw_ceil(cub, x, cub->column_h);
		draw_floor(cub, x, cub->column_h);

//
		cub->ray += FOV / cub->scene.screen_width;
		x++;
	}

	// printf("x: %d, y: %d\n", tx, ty);
	// printf("route: %f\n", cub->plr.route);
	// printf("x: %f\n", cub->pl r.x0);
	// printf("y: %f\n", cub->plr.y0);
	mlx_put_image_to_window(cub->vars.mlx, cub->vars.win, cub->win.img, 0, 0);
	return (0);
}

//      111111111111           
//      100000000001           
//      111100011111           
//         10001     1111      
// 1111111110001     1001      
// 1000000000001     1001111111
// 1111111111001     1000000001
//          1001     1001111111
// 1111111111001111111001      
// 100000000000000000N001      
// 1111111111111111111111      