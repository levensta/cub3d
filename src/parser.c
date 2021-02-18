/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 02:38:03 by levensta          #+#    #+#             */
/*   Updated: 2021/02/18 21:10:48 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_is_last(t_all *cub)
{
	if (cub->s_height && cub->s_width && \
	cub->scene.north && cub->scene.south && cub->scene.east && \
	cub->scene.west && cub->scene.sprite && cub->scene.flooring != -1 && \
	cub->scene.ceiling != -1)
		cub->scene.is_last = 1;
}

static void	check_all(t_all *cub)
{
	if (!cub->s_height || !cub->s_width || \
	!cub->scene.north || !cub->scene.south || !cub->scene.east || \
	!cub->scene.west || !cub->scene.sprite || cub->scene.flooring == -1 || \
	cub->scene.ceiling == -1 || !cub->scene.is_world_map)
		error("Your map is incomplete");
}

char		**make_map(t_list **head, int size)
{
	char	**map;
	int		i;
	t_list	*tmp;

	i = -1;
	tmp = *head;
	if (!(map = malloc(sizeof(char *) * (size + 1))))
		error(NULL);
	while (tmp)
	{
		map[++i] = tmp->content;
		tmp = tmp->next;
	}
	map[++i] = NULL;
	return (map);
}

int			checkers(t_all *cub, char **map, char **arr, int i)
{
	if (!ft_strcmp("R", arr[0]))
		get_resolution(cub, arr);
	else if (!ft_strcmp("NO", arr[0]))
		get_path(&(cub->scene.north), arr);
	else if (!ft_strcmp("SO", arr[0]))
		get_path(&(cub->scene.south), arr);
	else if (!ft_strcmp("WE", arr[0]))
		get_path(&(cub->scene.west), arr);
	else if (!ft_strcmp("EA", arr[0]))
		get_path(&(cub->scene.east), arr);
	else if (!ft_strcmp("S", arr[0]))
		get_path(&(cub->scene.sprite), arr);
	else if (!ft_strcmp("F", arr[0]))
		get_color(&cub->scene.flooring, map[i], -1);
	else if (!ft_strcmp("C", arr[0]))
		get_color(&cub->scene.ceiling, map[i], -1);
	else if (cub->scene.is_last)
	{
		if ((cub->scene.world_map = get_map(cub, &map[i])))
			free_array(arr);
		return (1);
	}
	else
		error("Invalid map");
	return (0);
}

void		parser(t_all *cub, char **map)
{
	int		i;
	char	**arr;

	i = 0;
	while (map[i])
	{
		if (!(arr = ft_split_ws(map[i])))
			error(NULL);
		if (arr[0])
		{
			check_is_last(cub);
			if (checkers(cub, map, arr, i))
				break ;
			free_array(arr);
		}
		else
			free(arr);
		i++;
	}
	cub->view_dist = (double)(cub->s_width / 2) / \
	tan(((60.0f * M_PI / 180.0f) / 2));
	check_all(cub);
}
