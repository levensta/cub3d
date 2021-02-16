/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:13:09 by levensta          #+#    #+#             */
/*   Updated: 2021/02/16 22:18:46 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_path(char **path, char **arr)
{
	int i;
	int fd;

	i = 0;
	while (arr[++i])
	{
		if (i >= 2 || *path)
			error("Check your paths of textures");
	}
	fd = open(arr[1], O_RDONLY);
	if (fd == -1 || ft_strcmp(".xpm", &arr[1][ft_strlen(arr[1]) - 4]))
		error("Check your paths of textures");
	close(fd);
	*path = ft_strdup(arr[1]);
	if (!(*path))
		error(NULL);
}
