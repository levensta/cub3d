/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:01:25 by levensta          #+#    #+#             */
/*   Updated: 2021/02/14 18:08:59 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_path(t_all *cub)
{
	cub->scene.north = 0;
	cub->scene.south = 0;
	cub->scene.west = 0;
	cub->scene.east = 0;
	cub->scene.sprite = 0;
}

void	free_path(t_all *cub)
{
	if (cub->scene.north)
		free(cub->scene.north);
	if (cub->scene.south)
		free(cub->scene.south);
	if (cub->scene.west)
		free(cub->scene.west);
	if (cub->scene.east)
		free(cub->scene.east);
	if (cub->scene.sprite)
		free(cub->scene.sprite);
	clear_path(cub);
}

void	clear_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		arr[i] = 0;
		i++;
	}
	arr = 0;
}

void	free_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
	clear_array(arr);
}

void	clear_scene(t_all *cub)
{
	cub->scene.flooring = -1;
	cub->scene.ceiling = -1;
	cub->s_width = 0;
	cub->s_height = 0;
	cub->scene.is_last = 0;
	cub->scene.is_only_plr = 0;
	cub->scene.is_world_map = 0;
	cub->column_h = 0;
	cub->scene.map_height = 0;
	cub->fd = 0;
	cub->save = 0;
	clear_path(cub);
}
