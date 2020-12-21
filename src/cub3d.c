/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:45:09 by levensta          #+#    #+#             */
/*   Updated: 2020/12/21 20:33:45 by levensta         ###   ########.fr       */
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
	(void)keycode;
    mlx_destroy_window(vars->mlx, vars->win);
	return(0);
}

int main ()
{
    t_data	img;
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 500, 500, "labirint");
	img.img = mlx_new_image(vars.mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, \
                                 &img.endian);
	
	// mlx_pixel_put(g_mlx, g_win, 250, 250, 0xFF0000);
	int i = 30;
	int j = 150;
	int k = 151;
	double r = 64;
	double g = 201;
	double blue = create_trgb(0, r, g, 255);
	// int purple = create_trgb(0, 232, 28, 255);
	while (i < 150)
	{
		my_mlx_pixel_put(&img, j, i, blue);
		i++;
		j = 150;
		
		while (j < k)
		{
			my_mlx_pixel_put(&img, j, i, blue);
			j++;
		}
		if (r < 232.0)
			r = r + (232.0 / 150.0);
		if (g > 201.0)
			g = g - (201.0 / 150.0);
		blue = create_trgb(0, r, g, 255);
		k++;
	}
	// circle(&img, 30, 30, 30, 0x00FF00FF);
	// line(&img, 1, 500, 2, 499, 0x00FF00FF);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	// mlx_key_hook(vars.win, &key_hook, NULL);
	// mlx_hook(vars.win, 2, 1L<<0, &close_win, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
// (232 - r) / 150
// Если требуется за 30 итераций пройти от числа 10 до 60. Шаг = (60-10)/30=5/3
// gccw -I /usr/local/include cub3d.c -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit