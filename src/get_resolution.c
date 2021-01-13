/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_resolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:12:20 by levensta          #+#    #+#             */
/*   Updated: 2021/01/13 23:12:33 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_resolution(t_all *cub, char **arr)
{ 
	int i;
	int j;

	i = 0;
	while (arr[++i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (i >= 3 || !ft_isdigit(arr[i][j]) || \
			cub->scene.screen_width || cub->scene.screen_height)
				error(2);
			j++;
		}
	}
	cub->scene.screen_width = ft_atoi(arr[1]);
	cub->scene.screen_height = ft_atoi(arr[2]);
	// check_screen_size
}
