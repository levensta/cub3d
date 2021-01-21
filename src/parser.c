/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 02:38:03 by levensta          #+#    #+#             */
/*   Updated: 2021/01/21 23:32:10 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_is_last(t_all *cub)
{
	if (cub->scene.screen_height && cub->scene.screen_width && \
	cub->scene.north && cub->scene.south && cub->scene.east && \
	cub->scene.west && cub->scene.floor[0] != -1 && \
	cub->scene.celling[0] != -1)
		cub->scene.is_last = 1;
		//  && cub->scene.sprite
}

void	check_all(t_all *cub)
{
	if (!cub->scene.screen_height || !cub->scene.screen_width || \
	!cub->scene.north || !cub->scene.south || !cub->scene.east || \
	!cub->scene.west || cub->scene.floor[0] == -1 || \
	cub->scene.celling[0] == -1 || !cub->scene.is_world_map)
	//  || !cub->scene.sprite
		error(5);
}

char	**make_map(t_list **head, int size)
{
	char    **map = ft_calloc(size + 1, sizeof(char *));
	int     i = -1;
	t_list  *tmp = *head;

	while (tmp)
	{
		map[++i] = tmp->content;
		tmp= tmp->next;
	}
	return (map);
}

int		checkers(t_all *cub, char **map, char **arr, int i)
{
	if (!ft_strcmp("R", arr[0]))
		get_resolution(cub, arr);
	else if (!ft_strcmp("NO", arr[0]))
		cub->scene.north = get_path(cub->scene.north, arr);
	else if (!ft_strcmp("SO", arr[0]))
		cub->scene.south = get_path(cub->scene.south, arr);
	else if (!ft_strcmp("WE", arr[0]))
		cub->scene.west = get_path(cub->scene.west, arr);
	else if (!ft_strcmp("EA", arr[0]))
		cub->scene.east = get_path(cub->scene.east, arr);
	// else if (!ft_strcmp("S", arr[0]))
	// 	get_path(&cub->scene.sprite, arr);
	else if (!ft_strcmp("F", arr[0]))
		get_color(cub->scene.floor, map[i]);
	else if (!ft_strcmp("C", arr[0]))
		get_color(cub->scene.celling, map[i]);
	else if (cub->scene.is_last)
	{
		if ((cub->scene.world_map = get_map(cub, &map[i])))
			free_array(arr);
		return (1);
	}
	else
		error(5);
	return (0);
}

void	parser(t_all *cub, char **map)
{
	int	i;
	char **arr;

	i = 0;
	while (map[i])
	{
		arr = ft_split_ws(map[i]);
		if (arr[0])
		{
			check_is_last(cub);
			if (checkers(cub, map, arr, i))
				break;
			free_array(arr);
		}
		i++;
	}
}

// gcc -g -Wall -Wextra -Werror src/parser.c ./src/ft_split_whitespaces.c libft/ft_strdup.c libft/ft_substr.c  libft/ft_lstnew.c libft/ft_lstsize.c ./libft/ft_lstadd_back.c ./libft/ft_atoi.c ./libft/ft_calloc.c ./libft/ft_strncmp.c ./libft/ft_bzero.c ./libft/ft_isdigit.c ./src/get_next_line.c ./src/get_next_line_utils.c ./src/ft_split_rgb.c -I ./includes -I ./libft -I ./minilibx_opengl

//      111111111111
//      100000000001
//      111100011111
//         10001     1111
// 1111111110001     1001
// 1000000000001     1001111111
// 1111111111001     1000000001
//          1001     1001111111
// 1111111111001111111001
// 100000000000000000N001
// 1111111111111111111111