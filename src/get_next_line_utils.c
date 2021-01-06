/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 23:16:52 by levensta          #+#    #+#             */
/*   Updated: 2021/01/06 01:10:41 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str && str[i] != '\0')
		i++;
	return (i);
}

int		tofind_c(char *s)
{
	int	i;

	i = -1;
	if (s)
	{
		while (s[++i])
		{
			if (s[i] == '\n')
				return (i);
		}
	}
	return (-1);
}

char	*gnl_strdup(const char *s1, char *rest)
{
	size_t	i;
	char	*s2;

	i = 0;
	if (!s1 || !(s2 = malloc((ft_strlen(s1) + 1) * sizeof(char))))
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	if (rest)
		free(rest);
	return (s2);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
		s1 = gnl_strdup("", s1);
	if (!s2)
		s2 = gnl_strdup("", s2);
	i = 0;
	j = 0;
	if (!(str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

void	*ft_memset(void *dest, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)dest;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (str);
}
