/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:14:24 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:14:27 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char		*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	int		f;

	i = 0;
	f = 0;
	if (!(*needle))
		return ((char *)haystack);
	while (haystack[i])
	{
		while (haystack[i + f] == needle[f])
		{
			f++;
			if (!(needle[f]))
			{
				while (i--)
					haystack++;
				return ((char *)haystack);
			}
		}
		f = 0;
		i++;
	}
	return (NULL);
}
