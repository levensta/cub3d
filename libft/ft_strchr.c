/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levensta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 21:48:56 by levensta          #+#    #+#             */
/*   Updated: 2020/11/02 23:16:19 by levensta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*s;

	i = 0;
	s = (char *)str;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (&s[i]);
		i++;
	}
	return (c == '\0' ? &s[i] : 0);
}