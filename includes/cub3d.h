/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:36:29 by levensta          #+#    #+#             */
/*   Updated: 2021/01/03 02:37:41 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define mapWidth 5
# define mapHeight 5
# define screenWidth 640
# define screenHeight 480
# define EPS 0.000001
# define FOV 60.0f/360.0f
# define W 13
# define A 0
# define S 1
# define D 2

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>

typedef struct  s_vars {
    void        *mlx;
    void        *win;
}               t_vars;

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct  s_player {
	float		x0;
	float		y0;
	float		route;
}               t_player;

typedef	struct	s_all {
	t_data		win;
	t_vars		vars;
	t_player	plr;
	float		dx;
	float		dy;
	float		ray;
	float		distance;
}                t_all;

void			ft_putchar(char c);
void			ft_putstr(char *s);
void			ft_putnbr(int n);
int				create_trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
int				invert_trgb(int trgb);
void	my_mlx_pixel_put(t_all *cub, int x, int y, int color);
void	ray_correct(float *ray);
int	frame_loop(t_all *cub);
void    clear_image(t_all *cub);

#endif