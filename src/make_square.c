/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:02:49 by levensta          #+#    #+#             */
/*   Updated: 2021/02/21 21:59:20 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	max_strlen(char **map)
{
	int		i;
	size_t	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

static char		*set_spaces(char *str, size_t n)
{
	int		i;
	char	*s;

	i = 0;
	if (!(s = malloc(sizeof(char) * (n))))
		error(NULL);
	s = ft_memset(s, ' ', n);
	s[n] = '\0';
	if (!(str = ft_strjoin(str, s)))
		error(NULL);
	free(s);
	return (str);
}

void			make_square(char **map)
{
	int		i;
	size_t	max;

	i = 0;
	max = max_strlen(map);
	while (map[i])
	{
		if (!map[i][0])
			error("Empty line in the map");
		if (ft_strlen(map[i]) < max)
			map[i] = set_spaces(map[i], max - ft_strlen(map[i]));
		i++;
	}
}
