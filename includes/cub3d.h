/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:36:29 by levensta          #+#    #+#             */
/*   Updated: 2021/01/12 20:10:38 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define mapWidth 10
# define mapHeight 9
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

typedef struct	s_map
{
	int			screen_width;
	int			screen_height;

	char		*north;
	char		*south;
	char		*east;
	char		*west;
	char		*sprite;
	int			floor[3];
	int			celling[3];
	
	int			is_last;
	int			is_only_plr;
	char		**world_map;
}				t_map;

typedef struct  s_tex {
    void        *img;
    char		*addr;
	int			width;
	int			height;
	int			line_length;
}               t_tex;

typedef	struct	s_all {
	t_data		win;
	t_vars		vars;
	t_player	plr;
	t_map		scene;
	t_tex		tex;
	char		**worldMap;
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

void	check_is_last(t_all *cub);
void	free_scene(t_all *cub);
void	free_path(t_all *cub);
void	free_array(char **arr);
char	**make_map(t_list **head, int size);
char		**ft_split_ws(char const *s);
char		**ft_split_rgb(char const *s);
void	get_resolution(t_all *cub, char **arr);
char	*get_path(char *path, char **arr);
int		get_map(t_all *cub, char **map);
void	error(int code);
void	get_color(int *rgb, char *color);

#endif