/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 02:38:03 by levensta          #+#    #+#             */
/*   Updated: 2021/01/09 23:44:38 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include <fcntl.h>

void	error(int code)
{
	write(1, "Error\n", 6);
	if (code == 1)
		write(1, "Your file does not exist or file extension is not .cube\n", 56);
	else if (code == 2)
		write(1, "Check your screen resolution\n", 29);
	else if (code == 3)
		write(1, "Check your paths of textures\n", 29);
	else if (code == 4)
		write(1, "Check your RGB params\n", 22);
	else if (code == 5)
		write(1, "Invalid map\n", 12);
	// очистить все, что только можно
	exit(code);
}

void	free_path(t_all *cub)
{
	// if (cub->scene.north)
	// 	free(cub->scene.north);
	cub->scene.north = 0;
	// if (cub->scene.south)
	// 	free(cub->scene.south);
	cub->scene.south = 0;
	// if (cub->scene.west)
	// 	free(cub->scene.west);
	cub->scene.west = 0;
	// if (cub->scene.east)
	// 	free(cub->scene.east);
	cub->scene.east = 0;
	// if (cub->scene.sprite)
	// 	free(cub->scene.sprite);
	cub->scene.sprite = 0;
}

void	free_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		arr[i] = 0;
		i++;
	}
	if (arr)
		free(arr);
	arr = 0;
}

void	free_scene(t_all *cub)
{
	int i;
	i = 0;
	while (i < 3)
	{
		cub->scene.floor[i] = -1;
		cub->scene.celling[i] = -1;
		i++;
	}
	cub->scene.screen_width = 0;
	cub->scene.screen_height = 0;
	cub->scene.is_last = 0;
	free_path(cub);
	if (cub->scene.map)
		free_array(cub->scene.map);
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

char	*get_path(char *path, char **arr)
{
	int i;

	i = 0;
	while(arr[++i])
	{
		if (i >= 2 || path)
			error(3);
	}
	return (path = ft_strdup(arr[1]));
	// printf("%s\n", cub->scene.north);
}

void	get_color(int *rgb, char *color)
{
	int		i;
	int		commas;
	char	**arr;
	
	i = -1;
	commas = 0;
	while (color[++i])
	{
		if (color[i] == ',')
			commas++;
	}
	if (commas != 2)
		error(4);
	i = 0;
	arr = ft_split_rgb(color);
	while (arr[++i])
	{
		if (i > 3 || rgb[i - 1] != -1)
			error(4);
		rgb[i - 1] = ft_atoi(arr[i]);
		if (rgb[i - 1] < 0 || rgb[i - 1] > 255)
			error(4);
		printf("%d,", rgb[i - 1]);
	}
}


void	check_forbidden_symbols(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_memchr("012NSWE \t\n", &str[i], 10))
			error(5);
		i++;
	}
}
void	get_map(t_all *cub, char **map)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	j = 0;
	while (map[i])
	{
		check_forbidden_symbols(map[i]);
		if ((arr = ft_split_ws(map[i])))
		{
			while (arr[j])
			{
				check_walls(arr[j]);
				j++;
			}
		}

		i++;
	}
}

int     main(int argc, char **argv)
{
	int		fd = open(argv[1], O_RDONLY);
	t_all	cub;
	char	*line = NULL;
	t_list	*head = NULL;
	char	**map;

	free_scene(&cub);
	if (argc == 2)
	{
		if (ft_strcmp(".cub", &argv[1][ft_strlen(argv[1] - 4)]))
			error(1);
		while (get_next_line(fd, &line) == 1)
			ft_lstadd_back(&head, ft_lstnew(line));
		ft_lstadd_back(&head, ft_lstnew(line));
		free(line);
		map = make_map(&head, ft_lstsize(head));
		int	i = 0;
		char **arr;
		// while (map[++i])
		// 	ft_putendl_fd(map[i], 1);
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
				else if (!cub.scene.is_last)
					get_map(&cub, map);
				free_array(arr);
			}
			i++;
		}


		printf("%d\n%d\n%s\n%s\n%s\n%s\n%s\n", cub.scene.screen_width, cub.scene.screen_height, cub.scene.north, \
		cub.scene.south, cub.scene.west, cub.scene.east, cub.scene.sprite);
		return (0);
	}
	return (0);
}

// gcc -g -Wall -Wextra -Werror src/parser.c ./src/ft_split_whitespaces.c libft/ft_strdup.c libft/ft_substr.c  libft/ft_lstnew.c libft/ft_lstsize.c ./libft/ft_lstadd_back.c ./libft/ft_atoi.c ./libft/ft_calloc.c ./libft/ft_strncmp.c ./libft/ft_bzero.c ./libft/ft_isdigit.c ./src/get_next_line.c ./src/get_next_line_utils.c ./src/ft_split_rgb.c -I ./includes -I ./libft -I ./minilibx_opengl