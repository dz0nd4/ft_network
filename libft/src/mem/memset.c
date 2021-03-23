/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:11:35 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:20:02 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *s;
	unsigned char set;

	s = (unsigned char *)b;
	set = (unsigned char)c;
	while (len-- > 0)
	{
		*s = set;
		s++;
	}
	return (b);
}
