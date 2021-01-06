/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 22:58:33 by levensta          #+#    #+#             */
/*   Updated: 2021/01/06 01:10:38 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 1

# include <unistd.h>
# include <stdlib.h>

typedef struct	s_gnl
{
	int			count;
	char		*buff;
	int			n;
	int			q;
	int			size;
}				t_gnl;

size_t			ft_strlen(const char *str);
int				tofind_c(char *s);
int				get_next_line(int fd, char **line);
char			*gnl_strdup(const char *s1, char *rest);
char			*gnl_strjoin(char *s1, char *s2);
void			*ft_memset(void *dest, int c, size_t n);
int				cursus(t_gnl *gnl, char **line, char **rest, int fd);

#endif
