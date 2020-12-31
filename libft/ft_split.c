/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:10:29 by levensta          #+#    #+#             */
/*   Updated: 2020/11/06 21:14:05 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		read_word(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

size_t		count_words(char const *s, char c)
{
	size_t amount;
	size_t i;

	amount = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			i += read_word(&s[i], c);
			amount++;
		}
		else
			i++;
	}
	return (amount);
}

void		*free_words(char **words)
{
	int		i;

	i = -1;
	while (words && words[++i])
		free(words[i]);
	if (words)
		free(words);
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	size_t	amount;
	size_t	len;
	char	**words;

	if (!s)
		return (NULL);
	if (!(words = (char **)malloc((count_words(s, c) + 1) * sizeof(char *))))
		return (NULL);
	len = 0;
	amount = 0;
	while (s[len] != '\0')
	{
		if (s[len] != c)
		{
			if (!(words[amount++] = ft_substr(s, len, read_word(&s[len], c))))
				return (free_words(words));
			len += read_word(&s[len], c);
		}
		else
			len++;
	}
	words[amount] = NULL;
	return (words);
}
