/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 22:39:44 by levensta          #+#    #+#             */
/*   Updated: 2021/01/27 22:04:41 by levensta         ###   ########.fr       */
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

void	draw_ceil(t_all *cub, int column_h)
{
		float	j;
		int i;

		if (column_h < 0)
			column_h = 0;
		i = (cub->scene.screen_height - column_h) / 2;
		j = -1;
		while (j++ < i)
			my_mlx_pixel_put(cub, cub->x, j, cub->scene.ceiling);
}

void	draw_floor(t_all *cub, int column_h)
{
	int j;

	if (column_h < 0)
		column_h = 0;
	j = (cub->scene.screen_height + column_h) / 2 - 1;
	while (j++ < cub->scene.screen_height)
		my_mlx_pixel_put(cub, cub->x, j, cub->scene.flooring);
}

void	draw_texture(t_all *cub, float hit, int size, int n)
{
	unsigned int	color;
	float			j;
	int				i;
	int				max;

	i = (cub->scene.screen_height - size) / 2;
	j = 0;
	max = (cub->scene.screen_height + size) / 2;
	if (i < 0)
	{
		j = ((float)cub->txt[n].height / (float)size) * (-i);
		i = 0;
		max = cub->scene.screen_height;
	}
	hit *= cub->txt[n].width;
	while (i < max)
	{
		color = *(unsigned int*)(cub->txt[n].addr + ((int)j * cub->txt[n].line_length + (int)hit * (cub->txt[n].bits_per_pixel / 8)));
		if (color != 0 && color != 0xFF000000)
			my_mlx_pixel_put(cub, cub->x, i, color);
		i++;
		j += (float)cub->txt[n].height / (float)size;
	}
}

void        d_s(t_all *cub, t_sprite sprite, float x1, float y1)
{
    t_sprite ang;
    t_sprite dist;
    t_sprite dp;
    int     tx;
    int     size;

	y1 = y1 + 0;
	x1 = x1 + 0;
    ang.x = cub->plr.route + 0.25f;
    if (ang.x > 1.0f)
        ang.x -= 1.0f;
    ang.x *= (2 * M_PI);
    dist.y = (float)(cub->scene.screen_width / 2) / tan(((60.0f * M_PI / 180.0f) / 2));
    dp.x = cub->plr.x0 - (sprite.x + 0.5f);
    dp.y = cub->plr.y0 - (sprite.y + 0.5f);
    sprite.distance = sqrtf(powf(cub->plr.x0 - (sprite.x + 0.5f), 2) + powf(cub->plr.y0 - (sprite.y + 0.5f), 2));
    ang.y = atan2(dp.y, dp.x) - ang.x; // абсолютное направление от игрока до спрайта
    size = dist.y / (cosf(ang.y) * sprite.distance); // ширина и высота спрайта (квадратный)
    tx = cub->scene.screen_width / 2 + tan(ang.y) * dist.y - size / 2; // точка пересечения луча со спрайтом
    if (size <= 0 || tx < -size || tx >= cub->scene.screen_width \
	|| cub->x < tx || cub->x >= tx + size)
        return ;
	if (sprite.distance <= sqrtf(powf(x1 - cub->plr.x0, 2) + powf(y1 - cub->plr.y0, 2)))
    	draw_texture(cub, ((cub->x - tx) / (float)size), size, 4);
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

int		find_repeat_spr(t_all *cub, int x1, int y1)
{
	int i;

	i = 0;
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
		while (j < cub->num_spr - 1)
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
void	find_sprite(t_all *cub, float x1, float y1)
{
	int i;

	i = 0;
	if (find_repeat_spr(cub, (int)floorf(x1), (int)floorf(y1)))
		return ;
	cub->sprite[cub->num_spr].distance = sqrtf(powf(cub->plr.x0 - (x1 + 0.5f), 2) + powf(cub->plr.y0 - (y1 + 0.5f), 2));
	cub->sprite[cub->num_spr].x = floorf(x1);
	cub->sprite[cub->num_spr].y = floorf(y1);
	cub->num_spr++;
	sort_sprites(cub);
}

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
	
    while (cub->x < cub->scene.screen_width)
    {
		wall = 0;
		cub->num_spr = 0;
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
					find_sprite(cub, x1, y1);
				else if (cub->scene.world_map[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS) - 1] == '2')
					find_sprite(cub, x1 - 1, y1);
				is_x = 1;
			}
			else if (y1 - floorf(y1) < EPS)
			{
				if (cub->scene.world_map[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS)] == '1')
					wall = 1;
				else if (cub->scene.world_map[(int)floorf(y1 + EPS) - 1][(int)floorf(x1 + EPS)] == '1')
					wall = 1;
				if (cub->scene.world_map[(int)floorf(y1 + EPS)][(int)floorf(x1 + EPS)] == '2')
					find_sprite(cub, x1, y1);
				else if (cub->scene.world_map[(int)floorf(y1 + EPS) - 1][(int)floorf(x1 + EPS)] == '2')
					find_sprite(cub, x1, y1 - 1);
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
		while (w < cub->num_spr)
		{
			d_s(cub, cub->sprite[w], x1, y1);
			cub->sprite[w].x = 0;
			cub->sprite[w].y = 0;
			cub->sprite[w].distance = 0;
			w++;
		}
		cub->ray += FOV / cub->scene.screen_width;
		cub->x++;
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