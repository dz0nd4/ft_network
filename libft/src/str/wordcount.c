/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordcount.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:14:51 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:14:27 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

size_t		ft_wordcount(const char *s, char c)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	if (s)
	{
		while (s[i])
		{
			while (s[i] == c && s[i])
				i++;
			while (s[i] != c && s[i])
			{
				if (s[i + 1] == c || !(s[i + 1]))
					count++;
				i++;
			}
		}
	}
	return (count);
}
