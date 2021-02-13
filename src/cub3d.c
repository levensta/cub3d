/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:45:09 by levensta          #+#    #+#             */
/*   Updated: 2021/02/13 21:28:01 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include <fcntl.h>

static void	textures_init(t_all *cub)
{
	int i;

	cub->txt[0].img = mlx_xpm_file_to_image(cub->vars.mlx, cub->scene.north, \
	&(cub->txt[0].width), &(cub->txt[0].height));
	cub->txt[0].addr = mlx_get_data_addr(cub->txt[0].img, \
	&(cub->txt[0].bpp), &(cub->txt[0].ll), &i);
	cub->txt[1].img = mlx_xpm_file_to_image(cub->vars.mlx, cub->scene.south, \
	&(cub->txt[1].width), &(cub->txt[1].height));
	cub->txt[1].addr = mlx_get_data_addr(cub->txt[1].img, \
	&(cub->txt[1].bpp), &(cub->txt[1].ll), &i);
	cub->txt[2].img = mlx_xpm_file_to_image(cub->vars.mlx, cub->scene.west, \
	&(cub->txt[2].width), &(cub->txt[2].height));
	cub->txt[2].addr = mlx_get_data_addr(cub->txt[2].img, \
	&(cub->txt[2].bpp), &(cub->txt[2].ll), &i);
	cub->txt[3].img = mlx_xpm_file_to_image(cub->vars.mlx, cub->scene.east, \
	&(cub->txt[3].width), &(cub->txt[3].height));
	cub->txt[3].addr = mlx_get_data_addr(cub->txt[3].img, \
	&(cub->txt[3].bpp), &(cub->txt[3].ll), &i);
	cub->txt[4].img = mlx_xpm_file_to_image(cub->vars.mlx, cub->scene.sprite, \
	&(cub->txt[4].width), &(cub->txt[4].height));
	cub->txt[4].addr = mlx_get_data_addr(cub->txt[4].img, \
	&(cub->txt[4].bpp), &(cub->txt[4].ll), &i);
}

static void	move(t_all *cub, float tmp, float *tx, float *ty)
{
	float	speed;

	speed = 15.0f;
	ray_correct(&tmp);
	if ((cub->keys.key_w && cub->keys.key_a) || (cub->keys.key_w && \
	cub->keys.key_d) || (cub->keys.key_s && cub->keys.key_a) \
	|| (cub->keys.key_s && cub->keys.key_d))
		speed *= 1.5f;
	if (cub->keys.key_w)
		*ty = *ty - cos(cub->plr.route * 2 * M_PI) / speed;
	if (cub->keys.key_w)
		*tx = *tx + sin(cub->plr.route * 2 * M_PI) / speed;
	if (cub->keys.key_s)
		*ty = *ty + cos(cub->plr.route * 2 * M_PI) / speed;
	if (cub->keys.key_s)
		*tx = *tx - sin(cub->plr.route * 2 * M_PI) / speed;
	if (cub->keys.key_a)
		*ty = *ty + cos(tmp * 2 * M_PI) / speed;
	if (cub->keys.key_a)
		*tx = *tx - sin(tmp * 2 * M_PI) / speed;
	if (cub->keys.key_d)
		*ty = *ty - cos(tmp * 2 * M_PI) / speed;
	if (cub->keys.key_d)
		*tx = *tx + sin(tmp * 2 * M_PI) / speed;
}

int			event_loop(t_all *cub)
{
	float	tx;
	float	ty;
	float	tmp;

	tx = cub->plr.x0;
	ty = cub->plr.y0;
	tmp = cub->plr.route + 0.25f;
	if (cub->keys.key_esc)
		escape(cub);
	if (cub->keys.key_left)
		cub->plr.route -= 0.0050f;
	if (cub->keys.key_right)
		cub->plr.route += 0.0050f;
	move(cub, tmp, &tx, &ty);
	if (cub->scene.world_map[(int)floorf(ty)][(int)floorf(cub->plr.x0)] != '1')
	// && cub->scene.world_map[(int)floorf(ty)][(int)floorf(cub->plr.x0)] != '2')
		cub->plr.y0 = ty;
	if (cub->scene.world_map[(int)floorf(cub->plr.y0)][(int)floorf(tx)] != '1')
	// && cub->scene.world_map[(int)floorf(cub->plr.y0)][(int)floorf(tx)] != '2')
		cub->plr.x0 = tx;
	ray_correct(&cub->plr.route);
	if (cub->keys.key_a || cub->keys.key_d || cub->keys.key_s || \
	cub->keys.key_w || cub->keys.key_left || cub->keys.key_right)
		frame_loop(cub);
	return (0);
}

int			rendering(t_all *cub)
{
	cub->dists = malloc(sizeof(float) * cub->s_width);
	cub->vars.mlx = mlx_init();
	cub->vars.win = mlx_new_window(cub->vars.mlx, cub->s_width, \
	cub->s_height, "cub3D");
	cub->win.img = mlx_new_image(cub->vars.mlx, cub->s_width, cub->s_height);
	cub->win.addr = mlx_get_data_addr(cub->win.img, &(cub->win.bpp), \
	&(cub->win.ll), &(cub->win.endian));
	textures_init(cub);
	key_null(cub);
	frame_loop(cub);
	if (cub->save)
		save_bmp(cub);
	mlx_loop_hook(cub->vars.mlx, event_loop, cub);
	mlx_hook(cub->vars.win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->vars.win, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->vars.win, 17, 1L << 17, escape, cub);
	mlx_loop(cub->vars.mlx);
	return (0);
}

int		main(int argc, char **argv)
{
	t_all	cub;
	char	*line;
	t_list	*head;
	char	**map;

	line = NULL;
	head = NULL;
	clear_scene(&cub);
	if (argc > 1 && argc < 4)
	{
		if ((cub.fd = open(argv[1], O_RDONLY)) == -1)
			error("Such file does not exist");
		if (ft_strcmp(".cub", &argv[1][ft_strlen(argv[1] - 4)]) \
			|| (argc == 3 && ft_strcmp("--save", argv[2])))
			error("Invalid arguments");
		if (argc == 3)
			cub.save = 1;
		while (get_next_line(cub.fd, &line) == 1)
			ft_lstadd_back(&head, ft_lstnew(line));
		ft_lstadd_back(&head, ft_lstnew(line));
		map = make_map(&head, ft_lstsize(head));
		parser(&cub, map);
		rendering(&cub);
	}
}
