/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 17:48:48 by dzonda            #+#    #+#             */
/*   Updated: 2020/12/21 21:53:02 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bits.h"

uint32_t	ft_swap_uint32(uint32_t *val)
{
	*val = ((*val << 8) & 0xFF00FF00) | ((*val >> 8) & 0xFF00FF);
	*val = (*val << 16) | (*val >> 16);
	return (*val);
}

uint64_t	ft_swap_uint64(uint64_t *val)
{
	*val = ((*val << 8) & 0xFF00FF00FF00FF00ULL) |
		((*val >> 8) & 0x00FF00FF00FF00FFULL);
	*val = ((*val << 16) & 0xFFFF0000FFFF0000ULL) |
		((*val >> 16) & 0x0000FFFF0000FFFFULL);
	*val = (*val << 32) | (*val >> 32);
	return (*val);
}
