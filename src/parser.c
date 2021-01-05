/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 02:38:03 by levensta          #+#    #+#             */
/*   Updated: 2021/01/05 03:58:19 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include <fcntl.h>

void	free_array(t_all *cub)
{
	int i;
	i = -1;
	while (++i < 3)
	{
		cub->scene.floor[i] = -1;
		cub->scene.celling[i] = -1;
	}
	i = -1;
	while (cub->scene.map[++i])
	{
		if (cub->scene.map[i])
			free(cub->scene.map[i]);
		cub->scene.map[i] = 0;
	}
}

void	free_scene(t_all *cub)
{
	cub->scene.screen_width = 0;
	cub->scene.screen_height = 0;
	cub->scene.is_last = 0;
	if (cub->scene.north)
		free(cub->scene.north);
	cub->scene.north = 0;
	if (cub->scene.south)
		free(cub->scene.south);
	cub->scene.south = 0;
	if (cub->scene.west)
		free(cub->scene.west);
	cub->scene.west = 0;
	if (cub->scene.east)
		free(cub->scene.east);
	cub->scene.east = 0;
	if (cub->scene.sprite)
		free(cub->scene.sprite);
	cub->scene.sprite = 0;
	free_array(cub);
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

void	check_is_last(t_all *cub)
{
	if (cub->scene.screen_height && cub->scene.screen_width && \
	cub->scene.north && cub->scene.south && cub->scene.east && \
	cub->scene.west && cub->scene.sprite && cub->scene.floor[0] != -1 && \
	cub->scene.celling[0] != -1)
		cub->scene.is_last = 1;
}
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
			if (i >= 3 || !ft_isdigit(arr[i][j]))
			{
				write(1, "Error\n", 6);
				exit (1);
			}
			j++;
		}
	}
	cub->scene.screen_width = ft_atoi(arr[1]);
	cub->scene.screen_height = ft_atoi(arr[2]);
	// check_screen_size
}

int     main(int argc, char **argv)
{
	int		fd = open(argv[1], O_RDONLY);
	t_all	cub;
	char	*line = NULL;
	t_list	*head = NULL;
	char	**map;

	// free_scene(&cub);
	if (argc == 2)
	{
		while (get_next_line(fd, &line) == 1)
			ft_lstadd_back(&head, ft_lstnew(line));
		ft_lstadd_back(&head, ft_lstnew(line));
		map = make_map(&head, ft_lstsize(head));
		int	i = 0;
		char **arr;
		// while (map[++i])
		// 	ft_putendl_fd(map[i], 1);
		while (map[i])
		{
			check_is_last(&cub);
			if ((arr = ft_split_ws(map[i])))
			{
				if (!ft_strncmp("R", arr[0], ft_strlen(arr[0])))
					get_resolution(&cub, arr);

				free(arr);
				printf("%d\n%d\n", cub.scene.screen_width, cub.scene.screen_height);
				return (0);
			}
			i++;
		}
	}
	return (0);
}