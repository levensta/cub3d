/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:02:49 by levensta          #+#    #+#             */
/*   Updated: 2021/01/16 20:01:53 by levensta         ###   ########.fr       */
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
	s = malloc(n * sizeof(char *) + 1);
	ft_memset(s, ' ', n);
	str = ft_strjoin(str, s);
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
		if (ft_strlen(map[i]) < max)
			map[i] = set_spaces(map[i], max - ft_strlen(map[i]));
		i++;
	}
}
