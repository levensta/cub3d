/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 21:29:43 by levensta          #+#    #+#             */
/*   Updated: 2021/02/08 21:50:10 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bmp_header(t_all *cub, int fd)
{
	int		t;
	short	d;

	write(fd, "BM", 2);
	t = 14 + 40 + cub->s_width * cub->s_height * 4;
	write(fd, &t, sizeof(t));
	d = 0;
	write(fd, &d, sizeof(d));
	write(fd, &d, sizeof(d));
	t = 14 + 40;
	write(fd, &t, sizeof(t));
}

void	image_header(t_all *cub, int fd)
{
	int		t;
	short	d;

	t = 40;
	write(fd, &t, sizeof(t));
	t = cub->s_width;
	write(fd, &t, sizeof(t));
	t = cub->s_height;
	write(fd, &t, sizeof(t));
	d = 1;
	write(fd, &d, sizeof(d));
	d = 32;
	write(fd, &d, sizeof(d));
	t = 0;
	write(fd, &t, sizeof(t));
	t = cub->s_width * cub->s_height * 4;
	write(fd, &t, sizeof(t));
	t = 2795;
	write(fd, &t, sizeof(t));
	write(fd, &t, sizeof(t));
	t = 0;
	write(fd, &t, sizeof(t));
	write(fd, &t, sizeof(t));
}

int		save_bmp(t_all *cub)
{
	int		fd;
	int		i;

	if ((fd = open("screenshot.bmp", O_RDWR | O_CREAT | O_TRUNC, 00600 | 00060 | 00006)) < 0)
		error("Crazy error from bmp");
	bmp_header(cub, fd);
	image_header(cub, fd);
	i = cub->s_height;
	while (--i >= 0)
		cub->win.addr += cub->s_width * 4;
	while (i < cub->s_height)
	{
		write(fd, cub->win.addr, cub->s_width* 4);
		cub->win.addr -= cub->s_width * 4;
		i++;
	}
	close(fd);
	ft_putendl_fd("Screenshot successfully created", 1);
	exit(0);
	return (0);
}
