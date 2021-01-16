/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_resolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:12:20 by levensta          #+#    #+#             */
/*   Updated: 2021/01/16 21:30:22 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_resolution(int *width, int *height)
{
	if (*width > MAC_WIDTH)
		*width = MAC_HEIGHT;
	if (*width < 321)
		*width = 321;
	if (*height > MAC_HEIGHT)
		*height = MAC_HEIGHT;
	if (*height < 201)
		*height = 200;
}

void		get_resolution(t_all *cub, char **arr)
{ 
	int i;
	int j;

	i = 0;
	while (arr[++i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (!ft_isdigit(arr[i][j]))
				error(2);
			j++;
		}
	}
	if (i != 3 || cub->scene.screen_width || cub->scene.screen_height)
		error(2);
	check_resolution(&(cub->scene.screen_width), &(cub->scene.screen_height));
	cub->scene.screen_width = ft_atoi(arr[1]);
	cub->scene.screen_height = ft_atoi(arr[2]);
	// check_screen_size
}
