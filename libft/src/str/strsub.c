/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:14:26 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:14:27 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char		*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	if (s)
	{
		i = -1;
		if (!(str = ft_strnew(len)))
			return (NULL);
		while (++i < (int)len)
		{
			str[i] = s[start];
			start++;
		}
		return (str);
	}
	return (NULL);
}
