/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memrev.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:11:30 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:10:35 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void	*ft_memrev(void *p, size_t len)
{
	size_t			i;
	char			c;
	unsigned char	*up;

	i = 0;
	c = 0;
	up = (unsigned char *)p;
	len -= 1;
	while (i < len)
	{
		c = up[i];
		up[i++] = up[len];
		up[len--] = c;
	}
	return (p);
}
