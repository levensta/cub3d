/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_resolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:12:20 by levensta          #+#    #+#             */
/*   Updated: 2021/02/09 23:17:18 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_screen_size(t_all *cub)
{
	int	real_width;
	int	real_height;
	mlx_get_screen_size(cub->vars.mlx, &real_width, &real_height);
	if (cub->s_width > real_width)
		cub->s_width = real_width;
	if (cub->s_width < 1)
		cub->s_width = 320;
	if (cub->s_height > real_height)
		cub->s_height = real_height;
	if (cub->s_height < 1)
		cub->s_height = 200;
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
				error("Check your screen size");
			j++;
		}
	}
	if (i != 3 || cub->s_width || cub->s_height)
		error("Check your screen size");
	cub->s_width = ft_atoi(arr[1]);
	cub->s_height = ft_atoi(arr[2]);
	if (!cub->save)
		check_screen_size(cub);
	if (!cub->save)
		if (ft_strlen(arr[1]) > 9)
			mlx_get_screen_size(cub->vars.mlx, &cub->s_width, &i);
		if (ft_strlen(arr[2]) > 9)
			mlx_get_screen_size(cub->vars.mlx, &i, &cub->s_height);
	printf("%d %d\n", cub->s_width, cub->s_height);
}