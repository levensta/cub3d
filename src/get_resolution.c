/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_resolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:12:20 by levensta          #+#    #+#             */
/*   Updated: 2021/02/08 21:48:50 by levensta         ###   ########.fr       */
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
				error("Check your screen resolution");
			j++;
		}
	}
	if (i != 3 || cub->s_width || cub->s_height)
		error("Check your screen resolution");
	if (!cub->save)
		if (ft_strlen(arr[1]) > 4 || ft_strlen(arr[2]) > 4)
			check_screen_size(&(cub->s_width), &(cub->s_height));;
	cub->s_width = ft_atoi(arr[1]);
	cub->s_height = ft_atoi(arr[2]);
	if (!cub->save)
		check_screen_size(&(cub->s_width), &(cub->s_height));
	printf("%d %d\n", cub->s_width, cub->s_height);
}