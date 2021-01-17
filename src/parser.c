/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 02:38:03 by levensta          #+#    #+#             */
/*   Updated: 2021/01/17 16:13:09 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include <fcntl.h>

void	check_is_last(t_all *cub)
{
	if (cub->scene.screen_height && cub->scene.screen_width && \
	cub->scene.north && cub->scene.south && cub->scene.east && \
	cub->scene.west && cub->scene.sprite && cub->scene.floor[0] != -1 && \
	cub->scene.celling[0] != -1)
		cub->scene.is_last = 1;
}

void	check_all(t_all *cub)
{
	if (!cub->scene.screen_height || !cub->scene.screen_width || \
	!cub->scene.north || !cub->scene.south || !cub->scene.east || \
	!cub->scene.west || !cub->scene.sprite || cub->scene.floor[0] == -1 || \
	cub->scene.celling[0] == -1 || !cub->scene.is_world_map)
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

int     main(int argc, char **argv)
{
	int		fd;
	t_all	cub;
	char	*line = NULL;
	t_list	*head = NULL;
	char	**map;

	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error(5);
	close(fd);
	clear_scene(&cub);
	if (argc == 2)
	{
		if (ft_strcmp(".cub", &argv[1][ft_strlen(argv[1] - 4)]))
			error(1);
		while (get_next_line(fd, &line) == 1)
			ft_lstadd_back(&head, ft_lstnew(line));
		ft_lstadd_back(&head, ft_lstnew(line));
		close(fd);
		// free(line);
		map = make_map(&head, ft_lstsize(head));
		int	i = 0;
		char **arr;
		while (map[i])
		{
			arr = ft_split_ws(map[i]);
			if (arr[0])
			{
				check_is_last(&cub);
				if (!ft_strcmp("R", arr[0]))
					get_resolution(&cub, arr);
				else if (!ft_strcmp("NO", arr[0]))
					cub.scene.north = get_path(cub.scene.north, arr);
				else if (!ft_strcmp("SO", arr[0]))
					cub.scene.south = get_path(cub.scene.south, arr);
				else if (!ft_strcmp("WE", arr[0]))
					cub.scene.west = get_path(cub.scene.west, arr);
				else if (!ft_strcmp("EA", arr[0]))
					cub.scene.east = get_path(cub.scene.east, arr);
				else if (!ft_strcmp("S", arr[0]))
					cub.scene.sprite = get_path(cub.scene.sprite, arr);
				else if (!ft_strcmp("F", arr[0]))
					get_color(cub.scene.floor, map[i]);
				else if (!ft_strcmp("C", arr[0]))
					get_color(cub.scene.celling, map[i]);
				else if (cub.scene.is_last)
				{
					if ((cub.scene.world_map = get_map(&cub, &map[i])))
						free_array(arr);
					break;
				}
				else
					error(5);
				free_array(arr);
			}
			i++;
		}
		// int m = 0;
		// while (cub.scene.world_map[m])
		// {
		// 	printf("%s\n", cub.scene.world_map[m]);
		// 	m++;
		// }
		check_all(&cub);

		printf("%d\n%d\n%s\n%s\n%s\n%s\n%s\n", cub.scene.screen_width, cub.scene.screen_height, cub.scene.north, \
		cub.scene.south, cub.scene.west, cub.scene.east, cub.scene.sprite);
		free_array(map);
		// free(line);
		free(head);
		return (0);
	}
	return (0);
}

// gcc -g -Wall -Wextra -Werror src/parser.c ./src/ft_split_whitespaces.c libft/ft_strdup.c libft/ft_substr.c  libft/ft_lstnew.c libft/ft_lstsize.c ./libft/ft_lstadd_back.c ./libft/ft_atoi.c ./libft/ft_calloc.c ./libft/ft_strncmp.c ./libft/ft_bzero.c ./libft/ft_isdigit.c ./src/get_next_line.c ./src/get_next_line_utils.c ./src/ft_split_rgb.c -I ./includes -I ./libft -I ./minilibx_opengl