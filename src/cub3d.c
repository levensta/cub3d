/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:45:09 by levensta          #+#    #+#             */
/*   Updated: 2021/01/19 23:42:14 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include <fcntl.h>

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

void	my_mlx_pixel_put(t_all *cub, int x, int y, unsigned int color)
{
    char	*dst;
	if (x < 0 || y < 0 || x >= screenWidth || y >= screenHeight)
		return ;
	dst = cub->win.addr + (y * cub->win.line_length + x * (cub->win.bits_per_pixel / 8));
	// dst = cub->screen.data + (y * cub->s_width + x) * 4;
	*(unsigned int*)dst = color;
}

int             loop(t_all *cub)
{
	float tx;
	float ty;
	float tmp = cub->plr.route + 0.25f;
	ray_correct(&tmp);
	if (cub->keys.key_esc)
	{
    	mlx_destroy_image(cub->vars.mlx, cub->txt[0].img);
    	mlx_destroy_image(cub->vars.mlx, cub->txt[1].img);
    	mlx_destroy_image(cub->vars.mlx, cub->txt[2].img);
    	mlx_destroy_image(cub->vars.mlx, cub->txt[3].img);
    	mlx_destroy_image(cub->vars.mlx, cub->win.img);
    	mlx_destroy_window(cub->vars.mlx, cub->vars.win);
		exit(0);
	}
	if (cub->keys.key_left) // <-
	{
		cub->plr.route -= 0.0050f;
		// printf("%f\n", cub->plr.route);
	}
	if (cub->keys.key_right) // ->
		cub->plr.route += 0.0050f;

	if (cub->keys.key_w)
	{
		ty = cub->plr.y0 - cos(cub->plr.route * 2 * M_PI) / SPEED;
		tx = cub->plr.x0 + sin(cub->plr.route * 2 * M_PI) / SPEED;
	}
	if (cub->keys.key_s)
	{
		ty = cub->plr.y0 + cos(cub->plr.route * 2 * M_PI) / SPEED;
		tx = cub->plr.x0 - sin(cub->plr.route * 2 * M_PI) / SPEED;
	}
	if (cub->keys.key_a)
	{
		ty = cub->plr.y0 + cos(tmp * 2 * M_PI) / SPEED;
		tx = cub->plr.x0 - sin(tmp * 2 * M_PI) / SPEED;
	}
	if (cub->keys.key_d)
	{
		ty = cub->plr.y0 - cos(tmp * 2 * M_PI) / SPEED;
		tx = cub->plr.x0 + sin(tmp * 2 * M_PI) / SPEED;
	}
	if (cub->scene.world_map[(int)floorf(ty)][(int)floorf(tx)] != '1')
	{
		cub->plr.x0 = tx;
		cub->plr.y0 = ty;
	}
	ray_correct(&cub->plr.route);
	if (cub->keys.key_a || cub->keys.key_d || cub->keys.key_s || cub->keys.key_w || \
	cub->keys.key_left || cub->keys.key_right)
		frame_loop(cub);
	// printf("route: %f\n", cub->plr.route);
	// printf("x: %f\n", cub->plr.x0);
	// printf("y: %f\n", cub->plr.y0);
	return(0);
}

void	ray_correct(float *ray)
{
	while (*ray < 0)
		*ray += 1;
    while (*ray >= 1)
		*ray -= 1;
}

void	textures_init(t_all *cub)
{
	int i;
	int k;

	char *textures[4] =
	{
		"./elmo.xpm",
		"./kermit.xpm",
		"./bert.xpm",
		"./cookie.xpm"
	};
	k = 0;
	while (k < 4)
	{
		cub->txt[k].img = mlx_xpm_file_to_image(cub->vars.mlx, textures[k], \
		&(cub->txt[k].width), &(cub->txt[k].height));
		cub->txt[k].addr = mlx_get_data_addr(cub->txt[k].img, \
		&(cub->txt[k].bits_per_pixel), &(cub->txt[k].line_length), &i);
		k++;
	}


	// cub->txt_so.img = mlx_xpm_file_to_image(cub->vars.mlx, "./kermit.xpm", \
	// &(cub->txt_so.width), &(cub->txt_so.height));
	// cub->txt_so.addr = mlx_get_data_addr(cub->txt_so.img, \
	// &(cub->txt_so.bits_per_pixel), &(cub->txt_so.line_length), &i);

	// cub->txt_we.img = mlx_xpm_file_to_image(cub->vars.mlx, "./bert.xpm", \
	// &(cub->txt_we.width), &(cub->txt_we.height));
	// cub->txt_we.addr = mlx_get_data_addr(cub->txt_we.img, \
	// &(cub->txt_we.bits_per_pixel), &(cub->txt_we.line_length), &i);

	// cub->txt_ea.img = mlx_xpm_file_to_image(cub->vars.mlx, "./cookie.xpm", \
	// &(cub->txt_ea.width), &(cub->txt_ea.height));
	// cub->txt_ea.addr = mlx_get_data_addr(cub->txt_ea.img, \
	// &(cub->txt_ea.bits_per_pixel), &(cub->txt_ea.line_length), &i);
}

int             key_release(int keycode, t_all *cub)
{
	if (keycode == A)
		cub->keys.key_a = 0;
	if (keycode == D)
		cub->keys.key_d = 0;
	if (keycode == S)
		cub->keys.key_s = 0;
	if (keycode == W)
		cub->keys.key_w = 0;
	if (keycode == LEFT)
		cub->keys.key_left = 0;
	if (keycode == RIGHT)
		cub->keys.key_right = 0;
	if (keycode == ESC)
		cub->keys.key_esc = 0;
	return (0);
}

int             key_press(int keycode, t_all *cub)
{
	if (keycode == A)
		cub->keys.key_a = 1;
	if (keycode == D)
		cub->keys.key_d = 1;
	if (keycode == S)
		cub->keys.key_s = 1;
	if (keycode == W)
		cub->keys.key_w = 1;
	if (keycode == LEFT)
		cub->keys.key_left = 1;
	if (keycode == RIGHT)
		cub->keys.key_right = 1;
	if (keycode == ESC)
		cub->keys.key_esc = 1;
	return (0);
}

void	key_null(t_all *cub)
{
	cub->keys.key_a = 0;
	cub->keys.key_d = 0;
	cub->keys.key_s = 0;
	cub->keys.key_w = 0;
	cub->keys.key_left = 0;
	cub->keys.key_right = 0;
	cub->keys.key_esc = 0;
}

int rendering(t_all *cub)
{
	// cub->plr.x0 = 5.5;
	// cub->plr.y0 = 4.5;
	cub->plr.route = 0;
	cub->vars.mlx = mlx_init();
	// char worldMap[mapHeight][mapWidth]=
	// {
	// "1111111111",
	// "1000000001",
	// "1000000001",
	// "1000000001",
	// "1000000001",
	// "1000000001",
	// "1000000001",
	// "1000000001",
	// "1111111111"
	// };

	// cub->worldMap = malloc (9 * sizeof(char *));
	// int w = 0;
	// while (w < 10)
	// {
	// 	cub->worldMap[w] = malloc(10);
	// 	cub->worldMap[w] = worldMap[w];
	// 	w++;
	// }
	cub->vars.win = mlx_new_window(cub->vars.mlx, screenWidth, screenHeight, "cub3D");
	cub->win.img = mlx_new_image(cub->vars.mlx, screenWidth, screenHeight);
	cub->win.addr = mlx_get_data_addr(cub->win.img, &(cub->win.bits_per_pixel), &(cub->win.line_length), \
                                 &(cub->win.endian));
	textures_init(cub);
	key_null(cub);
	// mlx_key_hook(cub->vars.win, key_hook, NULL);
	// frame_loop(&cub);
	frame_loop(cub);
	mlx_loop_hook(cub->vars.mlx, loop, cub);
	mlx_hook(cub->vars.win, 2, 1L<<0, key_press, cub);
	mlx_hook(cub->vars.win, 3, 1L<<1, key_release, cub);
	// mlx_hook(vars.win, 9, 1L<<4, &mouse_print, &vars);
	mlx_loop(cub->vars.mlx);
	return (0);
}

int     main(int argc, char **argv)
{
	t_all	cub;
	char	*line = NULL;
	t_list	*head = NULL;
	char	**map;

	if ((cub.fd = open(argv[1], O_RDONLY)) == -1)
		error(5);
	clear_scene(&cub);
	if (argc == 2)
	{
		if (ft_strcmp(".cub", &argv[1][ft_strlen(argv[1] - 4)]))
			error(1);
		while (get_next_line(cub.fd, &line) == 1)
			ft_lstadd_back(&head, ft_lstnew(line));
		ft_lstadd_back(&head, ft_lstnew(line));
		map = make_map(&head, ft_lstsize(head));
		parser(&cub, map);
		check_all(&cub);
		printf("%d\n%d\n%s\n%s\n%s\n%s\n%s\n", cub.scene.screen_width, cub.scene.screen_height, cub.scene.north, \
		cub.scene.south, cub.scene.west, cub.scene.east, cub.scene.sprite);
		rendering(&cub);
		free_array(map);
		// free(line);
		free(head);
		close(cub.fd);
	}
	return (0);
}
// (232 - r) / 150
// Если требуется за 30 итераций пройти от числа 10 до 60. Шаг = (60-10)/30=5/3
// gccw -I /usr/local/include cub3d.c ft_utils.c -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit