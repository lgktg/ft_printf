/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:12:23 by tgelu             #+#    #+#             */
/*   Updated: 2018/04/17 14:51:53 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_words(char const *str, char c)
{
	int i;
	int words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && !(str[i] == c))
		{
			i++;
			if (!str[i] || str[i] == c)
				words += 1;
		}
		if (str[i])
			i++;
	}
	return (words);
}

static void		ft_fill_str(char *dest, char const *src, int index, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[index + i];
		i++;
	}
	dest[i] = '\0';
}

static void		ft_strtbl(char **tbl, char const *str, int word_index, char c)
{
	int i;
	int size;
	int start;

	i = 0;
	while (str[i])
	{
		size = 0;
		while (str[i] && !(str[i] == c))
		{
			if (!str[i - 1] || str[i - 1] == c)
				start = i;
			size++;
			i++;
			if (!str[i] || str[i] == c)
			{
				if (!(tbl[++word_index] = malloc(size * sizeof(char))))
					return ;
				ft_fill_str(tbl[word_index], str, start, size);
			}
		}
		if (str[i])
			i++;
	}
}

char			**ft_strsplit(char const *str, char c)
{
	int		i;
	char	**s;

	i = 0;
	if (str == NULL)
		return (NULL);
	if (!(s = malloc((ft_count_words(str, c) + 1) * sizeof(char *))))
		return (NULL);
	ft_strtbl(s, str, -1, c);
	s[ft_count_words(str, c)] = 0;
	return (s);
}
