/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 02:38:03 by levensta          #+#    #+#             */
/*   Updated: 2021/01/03 03:45:10 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include <fcntl.h>

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
	i = -1;
	while (map[++i])
		ft_putendl_fd(map[i], 1);
	return (map);
}

int     main(int argc, char **argv)
{
	int     fd = open(argv[1], O_RDONLY);
	char    *line = NULL;
	t_list  *head = NULL;
    if (argc == 2)
    {
        while (get_next_line(fd, &line))
            ft_lstadd_back(&head, ft_lstnew(line));
        ft_lstadd_back(&head, ft_lstnew(line));
        make_map(&head, ft_lstsize(head));        
    }
    return (0);
}