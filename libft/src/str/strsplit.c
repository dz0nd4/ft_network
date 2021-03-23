/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:14:20 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:14:27 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char		**ft_strsplit(const char *s, char c)
{
	char	**tab;
	size_t	w;
	size_t	i;
	int		v;

	i = 0;
	if (!(s))
		return (NULL);
	w = ft_wordcount(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (w + 1))))
		return (NULL);
	v = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			tab[v++] = ft_strsub(s, ((int)i), ft_wordlen(s, c, i));
			i += ft_wordlen(s, c, i);
		}
	}
	tab[v] = (NULL);
	return (tab);
}
