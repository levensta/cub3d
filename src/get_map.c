/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:04:26 by levensta          #+#    #+#             */
/*   Updated: 2021/01/13 23:20:37 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_forbidden_symbols(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_memchr("012NSWE \n", str[i], 9))
			error(5);
		i++;
	}
}

static void	check_in_str(char **map, char const *s, int i, int j)
{
	int		m;

	m = 0;
	while (s[m])
	{
		if (map[i][0] == '0' || map[i][0] == '2' || (map[i][j] == s[m] && (map[i][j - 1] == ' ' || \
			map[i][j + 1] == ' ' || map[i][j + 1] == 0)))
			error(5);
		if (i > 0)
		{
			if (map[i][j] == s[m] && (map[i - 1][0] == 0 || (map[i - 1][j - 1] == ' ' \
				|| map[i - 1][j] == ' ' || map[i - 1][j + 1] == ' ')))
				error(5);
		}
		else if (s[m] == map[i][j])
			error(5);
		if (map[i][j] == s[m] && (map[i + 1] == 0 || (map[i + 1][j - 1] == ' ' \
			|| map[i + 1][j] == ' ' || map[i + 1][j + 1] == ' ')))
				error(5);
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

static void	check_player(char **map, int *is_only_plr)
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
				if (*is_only_plr == 1)
					error(5);
				else
					*is_only_plr = 1;
			}
			j++;
		}
		i++;
	}
	if (*is_only_plr == 0)
		error(5);
}

int			get_map(t_all *cub, char **map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	make_square(map);
	while (map[i])
	{
		check_forbidden_symbols(map[i]);
		check_outer_spaces(map);
		i++;
	}
	check_player(map, &cub->scene.is_only_plr);
	return (1);
}