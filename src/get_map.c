/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:04:26 by levensta          #+#    #+#             */
/*   Updated: 2021/02/08 23:39:38 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_forbidden_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_memchr("012NSWE \n", str[i], 9))
			error("Your map contains a forbidden characters");
		i++;
	}
}

static void	check_in_str(char **map, char const *s, int i, int j)
{
	int		m;

	m = 0;
	while (s[m])
	{
		if (map[i][0] == '0' || map[i][0] == '2' || (map[i][j] == s[m] \
		&& (map[i][j - 1] == ' ' || map[i][j + 1] == ' ' || !map[i][j + 1])))
			error("Invalid map");
		if (i > 0)
		{
			if (map[i][j] == s[m] && (!map[i - 1][0] || \
			(map[i - 1][j - 1] == ' ' || map[i - 1][j] == ' ' \
			|| map[i - 1][j + 1] == ' ')))
				error("Invalid map");
		}
		else if (s[m] == map[i][j])
			error("Invalid map");
		if (map[i][j] == s[m] && (!map[i + 1] || (map[i + 1][j - 1] == ' ' \
		|| map[i + 1][j] == ' ' || map[i + 1][j + 1] == ' ')))
			error("Invalid map");
		m++;
	}
}

static void	check_outer_spaces(char **map)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			check_in_str(map, "02NSWE", i, j);
			j++;
		}
		i++;
	}
}

void		set_route(float *route, char c)
{
	if (c == 'N')
		*route = 0;
	else if (c == 'E')
		*route = 0.25f;
	else if (c == 'S')
		*route = 0.5f;
	else if (c == 'W')
		*route = 0.75f;
}
static void	check_player(char **map, t_all *cub)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == 'N' || map[i][j] == 'S' \
			|| map[i][j] == 'W' || map[i][j] == 'E'))
			{
				if (cub->scene.is_only_plr == 1)
					error("Your map must be contain only one player");
				else
					cub->scene.is_only_plr = 1;
				cub->plr.x0 = j + 0.5f;
				cub->plr.y0 = i + 0.5f;
				set_route(&cub->plr.route, map[i][j]);
			}
			j++;
		}
		i++;
		cub->scene.map_height = i;
	}
	if (cub->scene.is_only_plr == 0)
		error("Your map must be contain only one player");
}

char		**get_map(t_all *cub, char **map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	cub->num_spr = 0;
	make_square(map);
	while (map[i])
	{
		check_forbidden_chars(map[i]);
		check_outer_spaces(map);
		cub->num_spr += count_sprites(map[i]);
		i++;
	}
	cub->sprite = malloc(sizeof(t_sprite) * cub->num_spr);
	check_player(map, cub);
	cub->scene.is_world_map = 1;
	return (map);
}
