/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:13:09 by levensta          #+#    #+#             */
/*   Updated: 2021/01/21 23:33:49 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_path(char *path, char **arr)
{
	int i;
	int fd;

	i = 0;
	while(arr[++i])
	{
		if (i >= 2 || path)
			error(3);
	}
	fd = open(arr[1], O_RDONLY);
	if (fd == -1)
		error(3);
	close(fd);
	return (path = ft_strdup(arr[1]));
}
