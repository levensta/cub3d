/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 04:09:38 by levensta          #+#    #+#             */
/*   Updated: 2021/01/04 22:02:25 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t		read_word(char const *s)
{
	size_t	i;

	i = 0;
	while ((s[i] != ' ' && s[i] != '\t') && s[i] != '\0')
		i++;
	return (i);
}

size_t		count_words(char const *s)
{
	size_t amount;
	size_t i;

	amount = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ' ' && s[i] != '\t')
		{
			i += read_word(&s[i]);
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

char		**ft_split_ws(char const *s)
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
		if (s[len] != ' ' && s[len] != '\t')
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
