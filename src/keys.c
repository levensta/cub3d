/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 23:04:27 by levensta          #+#    #+#             */
/*   Updated: 2021/01/29 23:09:25 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int				escape(t_all *cub)
{
	mlx_destroy_image(cub->vars.mlx, cub->txt[0].img);
	mlx_destroy_image(cub->vars.mlx, cub->txt[1].img);
	mlx_destroy_image(cub->vars.mlx, cub->txt[2].img);
	mlx_destroy_image(cub->vars.mlx, cub->txt[3].img);
	mlx_destroy_image(cub->vars.mlx, cub->txt[4].img);
	mlx_destroy_image(cub->vars.mlx, cub->win.img);
	mlx_destroy_window(cub->vars.mlx, cub->vars.win);
	exit(0);
	return (0);
}
