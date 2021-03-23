/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memalloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:10:52 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:19:52 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void		*ft_memalloc(size_t size)
{
	void	*p;

	if ((p = malloc(size)) == NULL)
		return (NULL);
	ft_memset(p, 0, size);
	return (p);
}
