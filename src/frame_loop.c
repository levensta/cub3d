/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 22:39:44 by levensta          #+#    #+#             */
/*   Updated: 2021/02/16 21:12:21 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	frame_loop(t_all *cub)
{
	char	is_x;

	is_x = 0;
	cub->x = 0;
	cub->ray = cub->plr.route - FOV / 2;
	ray_correct(&cub->ray);
	cub->num_spr = 0;
	while (cub->x < cub->s_width)
	{
		cub->x1 = cub->plr.x0;
		cub->y1 = cub->plr.y0;
		ray_correct(&cub->ray);
		raycasting(cub, &is_x);
		drawing_room(cub, is_x);
		cub->ray += FOV / cub->s_width;
		cub->x++;
	}
	find_dists(cub);
	sort_sprites(cub);
	drawing_sprites(cub);
	mlx_put_image_to_window(cub->vars.mlx, cub->vars.win, cub->win.img, 0, 0);
	return (0);
}
