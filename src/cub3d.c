/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:45:09 by levensta          #+#    #+#             */
/*   Updated: 2020/12/25 22:27:18 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

// int	deal_key(int key)
// {
// 	ft_putchar('X');
// 	mlx_pixel_put(g_mlx_ptr, g_win_ptr, 250, 250, 0xFFFFFF);
// 	return (0);
// }

void line(t_data *data, int x1, int x2, int y1, int y2, int color)
{
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    my_mlx_pixel_put(data, x2, y2, color);
    while(x1 != x2 || y1 != y2) 
   {
        my_mlx_pixel_put(data, x1, y1, color);
        int error2 = error * 2;
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            y1 += signY;
        }
    }
}

void	circle(t_data *data, int x1, int y1, int R, int color)
{
   int x = 0;
   int y = R;
   int delta = 1 - 2 * R;
   int error = 0;
   while (y >= 0)
   {
	   my_mlx_pixel_put(data, x1 + x, y1 + y, color);
	   my_mlx_pixel_put(data, x1 + x, y1 - y, color);
       my_mlx_pixel_put(data, x1 - x, y1 + y, color);
       my_mlx_pixel_put(data, x1 - x, y1 - y, color);
       error = 2 * (delta + y) - 1;
       if ((delta < 0) && (error <= 0))
	   {
           delta += 2 * ++x + 1;
           continue ;
	   }
       if ((delta > 0) && (error > 0))
	   {
           delta -= 2 * --y + 1;
           continue ;
	   }
       delta += 2 * (++x - --y);
   }
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int             key_hook(int keycode)
{
    printf("Hello from key_hook! code: %d\n", keycode);
	return (0);
}

int             close_win(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
    	mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return(0);
}

// int             mouse_print(int keycode, t_vars *vars)
// {
// 	(void)keycode;
// 	vars->win = mlx_mouse_hide();
// 	return(0);
// }

void	ray_correct(float *ray)
{
	while (*ray < 0)
		*ray += 1;
    while (*ray >= 1)
		*ray -= 1;
}

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1},
  {1,0,0,0,1},
  {1,0,0,0,1},
  {1,0,0,0,1},
  {1,1,1,1,1},
};

int main ()
{
    t_data	win;
	t_vars	vars;
	int x = 0;
	int wall = 0;
    float fov = 60/360;
	float x0 = 2.5, y0 = 2.5;  //x and y start position
	float x1 = 0, y1 = 0;
    float dx;
    float dy;
	float route = 0;
	float distance = 0;
    float ray = route - fov/2;
	float column_h;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, screenWidth, screenHeight, "labirint");
	win.img = mlx_new_image(vars.mlx, screenWidth, screenHeight);
	win.addr = mlx_get_data_addr(win.img, &win.bits_per_pixel, &win.line_length, \
                                 &win.endian);

    while (ray < route + fov/2)
    {
		x1 = x0;
		y1 = y0;
		ray_correct(&ray);
		while (!wall)
		{
			if (ray <= 0.5)
				dx = ceilf(x1) - x1;
			else
				dx = x1 - floorf(x1);
			if (ray >= 0.25 && ray < 0.75)
				dy = ceilf(y1) - y1;
			else   
				dy = y1 - floorf(y1);


			float a = tanf(ray * 2 * M_PI) * dy;
			float b = tanf(M_PI_2 - ray * 2 * M_PI) * dx;
			if (a < b)
			{
				if (ray <= 0.5)
					x1 += a;
				else
					x1 -= a;
				if (ray >= 0.25 && ray < 0.75)
					y1 = ceilf(y1);
				else
					y1 = floorf(y1);
			}
			else
			{
				if (ray <= 0.5)
					x1 = ceilf(x1);
				else
					x1 = floorf(x1);
				if (ray >= 0.25 && ray < 0.75)
					y1 += b;
				else
					y1 -= b;
			}



			if (ray >= 0.125 && ray < 0.375)
			{
				if (worldMap[(int)ceilf(x1)][(int)floor(y1)] == 1)
					wall = 1;
			}

			if (ray >= 0.375 && ray < 0.625)
			{
				if (worldMap[(int)floorf(x1)][(int)ceilf(y1)] == 1)
					wall = 1;
			}

			if (ray >= 0.625 && ray < 0.875)
			{
				if (worldMap[(int)floor(x1) - 1][(int)floor(y1)] == 1)
					wall = 1;
			}

			else
			{
				if (worldMap[(int)floor(x1)][(int)floor(y1) - 1] == 1)
					wall = 1;
			}

		}
		distance = sqrtf(powf(x0 - x1, 2) + powf(y0 - y1, 2));


		column_h = screenHeight / 2;
        column_h = (float)column_h / tanf((fov / 2) * (M_PI / 180.0f));
        column_h = (int)ceilf((float)column_h / distance);

		int i = 0;
		int j = screenHeight / 2;
		while (i < screenWidth)
		{
			while (j < screenHeight)
			{
				my_mlx_pixel_put(&win, i, j, 0x00FF00FF);
				j++;
			}
			i++;
		}
        ray += fov / screenWidth;
    }

	mlx_put_image_to_window(vars.mlx, vars.win, win.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, NULL);
	mlx_hook(vars.win, 2, 1L<<0, &close_win, &vars);
	// mlx_hook(vars.win, 9, 1L<<4, &mouse_print, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
// (232 - r) / 150
// Если требуется за 30 итераций пройти от числа 10 до 60. Шаг = (60-10)/30=5/3
// gccw -I /usr/local/include cub3d.c ft_utils.c -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit