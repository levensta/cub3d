/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:36:29 by levensta          #+#    #+#             */
/*   Updated: 2021/02/13 21:27:08 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define BONUS 0
# define EPS 0.000001
# define FOV 60.0f/360.0f
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124
# define ESC 53

# include "mlx.h"
# include "mlx_mms.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct	s_vars {
	void		*mlx;
	void		*win;
}				t_vars;

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bpp;
	int			ll;
	int			endian;
}				t_data;

typedef struct	s_player {
	float		x0;
	float		y0;
	float		route;
}				t_player;

typedef struct	s_map
{
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	char		*sprite;
	int			flooring;
	int			ceiling;
	char		is_last;
	char		is_only_plr;
	char		is_world_map;
	char		**world_map;
	int			map_height;
}				t_map;

typedef struct	s_tex {
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			ll;
	int			bpp;
}				t_tex;

typedef struct	s_sprite {
	float		x;
	float		y;
	float		distance;
	float		angle;
}				t_sprite;

typedef struct	s_keys {
	char		key_a;
	char		key_s;
	char		key_d;
	char		key_w;
	char		key_left;
	char		key_right;
	char		key_esc;
}				t_keys;

typedef struct	s_cost {
	int			a;
	int			w;
	int			s;
	int			d;
}				t_cost;

typedef	struct	s_all {
	t_keys		keys;
	t_data		win;
	t_vars		vars;
	t_player	plr;
	t_map		scene;
	t_tex		txt[5];
	t_sprite	*sprite;
	float		x1;
	float		y1;
	int			s_width;
	int			s_height;
	int			column_h;
	float		ray;
	int			fd;
	int			num_spr;
	float		*dists;
	float		view_dist;
	int			x;
	char		save;
}				t_all;

void			my_mlx_pixel_put(t_all *cub, int x, int y, unsigned int color);
int				create_trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
void			clear_scene(t_all *cub);
void			clear_array(char **arr);
void			clear_path(t_all *cub);
void			clear_image(t_all *cub);
void			free_array(char **arr);
void			free_path(t_all *cub);
void			error(char *str);
void			ray_correct(float *ray);
void			set_route(float *route, char c);
char			**make_map(t_list **head, int size);
void			parser(t_all *cub, char **map);
int				checkers(t_all *cub, char **map, char **arr, int i);
char			**ft_split_ws(char const *s);
void			get_resolution(t_all *cub, char **arr);
char			*get_path(char *path, char **arr);
void			get_color(int *rgb, char *color, int i);
char			**get_map(t_all *cub, char **map);
void			make_square(char **map);
int				rendering(t_all *cub);
int				event_loop(t_all *cub);
void			key_null(t_all *cub);
int				key_press(int keycode, t_all *cub);
int				key_release(int keycode, t_all *cub);
int				escape(t_all *cub);
int				save_bmp(t_all *cub);
int				frame_loop(t_all *cub);
void			raycasting(t_all *cub, char *is_x);
void			drawing_room(t_all *cub, char is_x);
void			draw_texture(t_all *cub, float hit, int size, int n);
void			draw_floor(t_all *cub, int column_h);
void			draw_ceil(t_all *cub, int column_h);
int				count_sprites(char *str);
void			find_sprite(t_all *cub, int x1, int y1);
void			find_dists(t_all *cub);
void			sort_sprites(t_all *cub);
void			drawing_sprites(t_all *cub);
void			draw_sprite(t_all *cub, int size, int x_start, float dist);

#endif
