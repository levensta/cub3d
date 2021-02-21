/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:42:43 by levensta          #+#    #+#             */
/*   Updated: 2021/02/21 21:20:40 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		add_rest(char **rest, char **line)
{
	int		n;

	if ((n = tofind_c(*rest)) < 0)
	{
		*line = gnl_strjoin(*line, *rest);
		free(*rest);
		*rest = 0;
		return (0);
	}
	else
	{
		(*rest)[n] = '\0';
		*line = gnl_strjoin(*line, *rest);
		*rest = gnl_strdup(&((*rest)[n + 1]), *rest);
	}
	return (1);
}

int		cursus(t_gnl *gnl, char **line, char **rest, int fd)
{
	if (*rest)
		gnl->q = add_rest(rest, line);
	while (!gnl->q && gnl->count > 0)
	{
		gnl_memset(gnl->buff, '\0', gnl->size + 1);
		if ((gnl->count = read(fd, gnl->buff, gnl->size)) <= 0)
			break ;
		if ((gnl->n = tofind_c(gnl->buff)) > -1)
		{
			gnl->buff[gnl->n] = '\0';
			*line = gnl_strjoin(*line, gnl->buff);
			*rest = gnl_strdup(&gnl->buff[gnl->n + 1], *rest);
			break ;
		}
		else
			*line = gnl_strjoin(*line, gnl->buff);
	}
	free(gnl->buff);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*rest;
	t_gnl		gnl;

	gnl.size = BUFFER_SIZE;
	if (fd < 0 || gnl.size < 1 || !line || !(gnl.buff = malloc(gnl.size + 1)))
		return (-1);
	*line = gnl_strdup("", 0);
	gnl.count = 1;
	gnl.q = 0;
	cursus(&gnl, line, &rest, fd);
	if (gnl.count == -1)
		return (-1);
	gnl.count = gnl.count || gnl_strlen(rest);
	if (gnl.count)
		return (1);
	if (rest)
	{
		free(rest);
		rest = 0;
	}
	return (0);
}
