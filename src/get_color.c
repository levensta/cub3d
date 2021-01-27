/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:10:04 by levensta          #+#    #+#             */
/*   Updated: 2021/01/24 22:59:54 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static size_t	read_word(char const *s)
{
	size_t	i;

	i = 0;
	while ((s[i] != ' ' && s[i] != '\t' && s[i] != ',') && s[i] != '\0')
		i++;
	return (i);
}

static size_t	count_words(char const *s)
{
	size_t amount;
	size_t i;

	amount = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != ',')
		{
			i += read_word(&s[i]);
			amount++;
		}
		else
			i++;
	}
	return (amount);
}

static void		*free_words(char **words)
{
	int		i;

	i = -1;
	while (words && words[++i])
		free(words[i]);
	if (words)
		free(words);
	return (NULL);
}

static char		**ft_split_rgb(char const *s)
{
	size_t	amount;
	size_t	len;
	char	**words;

	if (!s)
		return (NULL);
	if (!(words = (char **)malloc((count_words(s) + 1) * sizeof(char *))))
		return (NULL);
	len = 0;
	amount = 0;
	while (s[len] != '\0')
	{
		if (s[len] != ' ' && s[len] != '\t' && s[len] != ',')
		{
			if (!(words[amount++] = ft_substr(s, len, read_word(&s[len]))))
				return (free_words(words));
			len += read_word(&s[len]);
		}
		else
			len++;
	}
	words[amount] = NULL;
	return (words);
}

void		get_color(int *rgb, char *color)
{
	int		i;
	int		tmp[3];
	int		commas;
	char	**arr;
	
	i = -1;
	commas = 0;
	while (color[++i])
	{
		if (color[i] == ',')
			commas++;
	}
	i = 0;
	arr = ft_split_rgb(color);
	while (arr[++i])
	{
		if (*rgb != -1 || ft_strlen(arr[i]) > 3)
			error(4);
		tmp[i - 1] = ft_atoi(arr[i]);
		if (tmp[i - 1] < 0 || tmp[i - 1] > 255)
			error(4);
	}
	*rgb = create_trgb(0, tmp[0], tmp[1], tmp[2]);
	if (!arr || commas != 2 || i != 4)
		error(4);
	free_array(arr);
}