/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:11:03 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:09:59 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void		*ft_memchr(const void *src, int c, size_t n)
{
	unsigned char	*s;
	unsigned char	ch;
	size_t			i;

	s = (unsigned char *)src;
	ch = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (s[i] == ch)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
