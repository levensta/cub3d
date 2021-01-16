/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:01:25 by levensta          #+#    #+#             */
/*   Updated: 2021/01/16 20:04:52 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	reset_path(t_all *cub)
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
	reset_path(cub);
}

void	reset_array(char **arr)
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
	reset_array(arr);
}

void	reset_scene(t_all *cub)
{
	int i;
	i = 0;
	while (i < 3)
	{
		cub->scene.floor[i] = -1;
		cub->scene.celling[i] = -1;
		i++;
	}
	cub->scene.screen_width = 0;
	cub->scene.screen_height = 0;
	cub->scene.is_last = 0;
	cub->scene.is_only_plr = 0;
	cub->scene.is_world_map = 0;
	reset_path(cub);
	// reset_array(cub->scene.world_map);
	// if (cub->scene.world_map)
	// 	free_array(cub->scene.world_map);
}
