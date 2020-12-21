/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:36:29 by levensta          #+#    #+#             */
/*   Updated: 2020/12/21 20:22:36 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include "mlx.h"
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

// t_vars          g_vars;

void	*g_mlx;
void	*g_win;

void			ft_putchar(char c);
void			ft_putstr(char *s);
void			ft_putnbr(int n);
int				create_trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
int				invert_trgb(int trgb);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif