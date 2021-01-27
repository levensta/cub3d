/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_resolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:12:20 by levensta          #+#    #+#             */
/*   Updated: 2021/01/24 22:58:56 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_screen_size(int *width, int *height)
{
	if (*width > MAC_WIDTH)
		*width = MAC_WIDTH;
	if (*width < 1)
		*width = 320;
	if (*height > MAC_HEIGHT)
		*height = MAC_HEIGHT;
	if (*height < 1)
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
	if (ft_strlen(arr[1]) > 4 || ft_strlen(arr[2]) > 4)
		error(2);
	cub->scene.screen_width = ft_atoi(arr[1]);
	cub->scene.screen_height = ft_atoi(arr[2]);
	printf("%d, %d\n", cub->scene.screen_width, cub->scene.screen_height);
	check_screen_size(&(cub->scene.screen_width), &(cub->scene.screen_height));
}

// 1111111111111111111111111
// 1222200000222200000000001
// 1222200000222200000000001
// 1222200000222200000000001
// 1222200000222200000000001
// 1222200000222200000000001
// 1222200000222200000N00001
// 1222200000222200000000001
// 1222200000222200000000001
// 1222200000222200000000001
// 1222200000222200000000001
// 1222200000222200000000001
// 1222200000222200000000001
// 1111111111111111111111111