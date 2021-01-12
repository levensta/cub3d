/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 02:38:03 by levensta          #+#    #+#             */
/*   Updated: 2021/01/12 23:30:18 by levensta         ###   ########.fr       */
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
	else if (code == 101)
		write(1, "You're crazy. Error of malloc\n", 30);
	//
	else if (code == 105)
		printf("105-105-105-105");
	else if (code == 106)
		printf("106-106-106-106");
	else if (code == 107)
		printf("107-107-107-107");
	else if (code == 108)
		printf("108-108-108-108");
	else if (code == 109)
		printf("109-109-109-109");
	// очистить все, что только можно
	exit(code);
}

void	reset_path(t_all *cub)
{
	cub->scene.north = 0;
	cub->scene.south = 0;
	cub->scene.west = 0;
	cub->scene.east = 0;
	cub->scene.sprite = 0;
}

void	free_path(t_all *cub)
{
	if (cub->scene.north)
		free(cub->scene.north);
	if (cub->scene.south)
		free(cub->scene.south);
	if (cub->scene.west)
		free(cub->scene.west);
	if (cub->scene.east)
		free(cub->scene.east);
	if (cub->scene.sprite)
		free(cub->scene.sprite);
	reset_path(cub);
}

void	reset_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		arr[i] = 0;
		i++;
	}
	arr = 0;
}

void	free_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
	reset_array(arr);
}

void	reset_scene(t_all *cub)
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
	cub->scene.is_only_plr = 0;
	reset_path(cub);
	// reset_array(cub->scene.world_map);
	// if (cub->scene.world_map)
	// 	free_array(cub->scene.world_map);
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
		// printf("%d,", rgb[i - 1]); // del
	}
}


void	check_forbidden_symbols(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_memchr("012NSWE \n", str[i], 9))
			error(5);
		i++;
	}
}


// void	check_in_str(char **map, int i, int j)
// {
// 	int		m;
// 	char	*symbols;

// 	m = 0;
// 	symbols = "02NSWE";
// 	while (symbols[m])
// 	{
// 		if (map[i][j] == symbols[m] && (map[i][j - 1] == ' ' || map[i][j + 1] == ' '))
// 			error(105);
// 		if (map[i][j] == symbols[m] && (map[i - 1][j - 1] == ' ' \
// 			|| map[i - 1][j] == ' ' || map[i - 1][j + 1] == ' '))
// 			error(106);
// 		if (map[i][j] == symbols[m] && (map[i + 1][j - 1] == ' ' \
// 			|| map[i + 1][j] == ' ' || map[i + 1][j + 1] == ' '))
// 			error(107);
// 		m++;
// 	}
// }

void	check_in_str(char **map, int i, int j)
{
	int		m;
	char	*symbols;

	m = 0;
	symbols = "02NSWE";
	while (symbols[m])
	{
		if (map[i][j] == symbols[m] && (map[i][j - 1] == ' ' || map[i][j + 1] == ' ' || map[i][j + 1] == '\0'))
			error(105);
		if (map[i][j] == symbols[m] && (map[i - 1][j - 1] == ' ' \
			|| map[i - 1][j] == ' ' || map[i - 1][j + 1] == ' '))
			error(106);
		if (map[i][j] == symbols[m] && (map[i + 1][j - 1] == ' ' \
		|| map[i + 1][j] == ' ' || map[i + 1][j + 1] == ' ' || map[i + 1][0] == '\0'))
			error(107);
		m++;
	}
}


void	check_outer_spaces(char **map)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			check_in_str(map, i, j);
			j++;
		}
		i++;
	}
}

void	check_player(char **map, int *is_only_plr)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == 'N' || map[i][j] == 'S' \
			|| map[i][j] == 'W' || map[i][j] == 'E'))
			{
				if (*is_only_plr == 1)
					error(108);
				else
					*is_only_plr = 1;
			}
			j++;
		}
		i++;
	}
	if (*is_only_plr == 0)
		error(109);
}


size_t	max_strlen(char **map)
{
	int		i;
	size_t	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

char	*set_spaces(char *str, size_t n)
{
	int		i;
	char	*s;
	i = 0;
	s = malloc(n * sizeof(char *) + 1);
	ft_memset(s, ' ', n);
	str = ft_strjoin(str, s);
	free(s);
	return (str);
}
void	make_square(char **map)
{
	int		i;
	size_t	max;
	
	i = 0;
	max = max_strlen(map);
	// write(1, "\n", 1);
	while (map[i])
	{
		if (ft_strlen(map[i]) < max)
			map[i] = set_spaces(map[i], max - ft_strlen(map[i]));
		printf("|%s|\n", map[i]);
		i++;
	}
}

int		get_map(t_all *cub, char **map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	make_square(map);
	// printf("\n|%s|\n", map[4]);
	while (map[i])
	{
		check_forbidden_symbols(map[i]);
		check_outer_spaces(map);
		i++;
	}
	check_player(map, &cub->scene.is_only_plr);
	return (1);
}

int     main(int argc, char **argv)
{
	int		fd = open(argv[1], O_RDONLY);
	t_all	cub;
	char	*line = NULL;
	t_list	*head = NULL;
	char	**map;

	reset_scene(&cub);
	if (argc == 2)
	{
		if (ft_strcmp(".cub", &argv[1][ft_strlen(argv[1] - 4)]))
			error(1);
		while (get_next_line(fd, &line) == 1)
			ft_lstadd_back(&head, ft_lstnew(line));
		ft_lstadd_back(&head, ft_lstnew(line));
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
					if (get_map(&cub, &map[i]))
						free_array(arr);
					break;
				}
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