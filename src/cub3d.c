/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:45:09 by levensta          #+#    #+#             */
/*   Updated: 2021/01/11 23:23:47 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	deal_key(int key)
// {
// 	ft_putchar('X');
// 	mlx_pixel_put(g_mlx_ptr, g_win_ptr, 250, 250, 0xFFFFFF);
// 	return (0);
// }

// void line(t_data *data, int x1, int x2, int y1, int y2, int color)
// {
//     const int deltaX = abs(x2 - x1);
//     const int deltaY = abs(y2 - y1);
//     const int signX = x1 < x2 ? 1 : -1;
//     const int signY = y1 < y2 ? 1 : -1;
//     int error = deltaX - deltaY;
//     my_mlx_pixel_put(data, x2, y2, color);
//     while(x1 != x2 || y1 != y2) 
//    {
//         my_mlx_pixel_put(data, x1, y1, color);
//         int error2 = error * 2;
//         if(error2 > -deltaY) 
//         {
//             error -= deltaY;
//             x1 += signX;
//         }
//         if(error2 < deltaX) 
//         {
//             error += deltaX;
//             y1 += signY;
//         }
//     }
// }

// void	circle(t_data *data, int x1, int y1, int R, int color)
// {
//    int x = 0;
//    int y = R;
//    int delta = 1 - 2 * R;
//    int error = 0;
//    while (y >= 0)
//    {
// 	   my_mlx_pixel_put(data, x1 + x, y1 + y, color);
// 	   my_mlx_pixel_put(data, x1 + x, y1 - y, color);
//        my_mlx_pixel_put(data, x1 - x, y1 + y, color);
//        my_mlx_pixel_put(data, x1 - x, y1 - y, color);
//        error = 2 * (delta + y) - 1;
//        if ((delta < 0) && (error <= 0))
// 	   {
//            delta += 2 * ++x + 1;
//            continue ;
// 	   }
//        if ((delta > 0) && (error > 0))
// 	   {
//            delta -= 2 * --y + 1;
//            continue ;
// 	   }
//        delta += 2 * (++x - --y);
//    }
// }

void	my_mlx_pixel_put(t_all *cub, int x, int y, int color)
{
    char	*dst;
	if (x < 0 || y < 0 || x >= screenWidth || y >= screenHeight)
		return ;
	dst = cub->win.addr + (y * cub->win.line_length + x * (cub->win.bits_per_pixel / 8));
	// dst = cub->screen.data + (y * cub->s_width + x) * 4;
	*(unsigned int*)dst = color;
}

// int             key_hook(int keycode)
// {
//     printf("Hello from key_hook! code: %d\n", keycode);
// 	return (0);
// }

int             key_press(int keycode, t_all *cub)
{
	float tx;
	float ty;
	float tmp = cub->plr.route + 0.25f;
	ray_correct(&tmp);
	if (keycode == 53)
	{
    	mlx_destroy_window(cub->vars.mlx, cub->vars.win);
		exit(0);
	}
	if (keycode == 123) // <-
	{
		cub->plr.route -= 0.05;
		// printf("%f\n", cub->plr.route);
	}
	if (keycode == 124) // ->
		cub->plr.route += 0.05;

	if (keycode == W)
	{
		ty = cub->plr.y0 - cos(cub->plr.route * 2 * M_PI);
		tx = cub->plr.x0 + sin(cub->plr.route * 2 * M_PI);
	}
	if (keycode == S)
	{
		ty = cub->plr.y0 + cos(cub->plr.route * 2 * M_PI);
		tx = cub->plr.x0 - sin(cub->plr.route * 2 * M_PI);
	}
	if (keycode == A) // 
	{
		ty = cub->plr.y0 + cos(tmp * 2 * M_PI);
		tx = cub->plr.x0 - sin(tmp * 2 * M_PI);
	}
	if (keycode == D)
	{
		ty = cub->plr.y0 - cos(tmp * 2 * M_PI);
		tx = cub->plr.x0 + sin(tmp * 2 * M_PI);
	}
	if (cub->worldMap[(int)floorf(ty)][(int)floorf(tx)] != '1')
	{
		cub->plr.x0 = tx;
		cub->plr.y0 = ty;
	}
	ray_correct(&cub->plr.route);
	printf("route: %f\n", cub->plr.route);
	printf("x: %f\n", cub->plr.x0);
	printf("y: %f\n", cub->plr.y0);
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

int main ()
{
	t_all	cub;
	cub.plr.x0 = 5.5;
	cub.plr.y0 = 4.5;
	cub.plr.route = 0;
	cub.vars.mlx = mlx_init();
	char worldMap[mapHeight][mapWidth]=
	{
	"1111111111",
	"1000000001",
	"1000000001",
	"1000000001",
	"100000001",
	"1000000001",
	"1000000001",
	"1000000001",
	"1111111111"
	};

	cub.worldMap = malloc (9 * sizeof(char *));
	int w = 0;
	while (w < 10)
	{
		cub.worldMap[w] = malloc(10);
		cub.worldMap[w] = worldMap[w];
		w++;
	}
	int		i;

	cub.vars.win = mlx_new_window(cub.vars.mlx, screenWidth, screenHeight, "cub3D");
	cub.win.img = mlx_new_image(cub.vars.mlx, screenWidth, screenHeight);
	cub.win.addr = mlx_get_data_addr(cub.win.img, &cub.win.bits_per_pixel, &cub.win.line_length, \
                                 &cub.win.endian);
	mlx_loop_hook(cub.vars.mlx, frame_loop, &cub);
	cub.tex.img = mlx_xpm_file_to_image(cub.vars.mlx, "./elmo.xpm", &cub.tex.width, &cub.tex.height);
	cub.tex.addr = mlx_get_data_addr(cub.tex.img, &i, &cub.tex.line_length, &i);
	// mlx_key_hook(cub.vars.win, key_hook, NULL);
	mlx_hook(cub.vars.win, 2, 1L<<0, key_press, &cub);
	// mlx_hook(vars.win, 9, 1L<<4, &mouse_print, &vars);
	mlx_loop(cub.vars.mlx);
	return (0);
}
// (232 - r) / 150
// Если требуется за 30 итераций пройти от числа 10 до 60. Шаг = (60-10)/30=5/3
// gccw -I /usr/local/include cub3d.c ft_utils.c -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit