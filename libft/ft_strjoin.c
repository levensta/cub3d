/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:09:41 by levensta          #+#    #+#             */
/*   Updated: 2021/01/12 23:07:35 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		len1;
	int		len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(str = malloc((len1 + len2) * sizeof(char))))
		return (NULL);
	ft_strlcpy(&str[ft_strlcpy(str, s1, len1 + 1)], s2, len2 + 1);
	free(s1);
	return (str);
}
