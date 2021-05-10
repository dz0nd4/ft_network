/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 17:41:54 by dzonda            #+#    #+#             */
/*   Updated: 2020/03/01 14:58:13 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bits.h"

t_uint32	ft_rotr_uint32(t_uint32 word, t_uint32 bits)
{
	return ((word >> bits) | (word << (32 - bits)));
}

t_uint32	ft_rotl_uint32(t_uint32 word, t_uint32 bits)
{
	return ((word << bits) | (word >> (32 - bits)));
}

t_uint64	ft_rotr_uint64(t_uint64 word, t_uint64 bits)
{
	return ((word >> bits) | (word << (64 - bits)));
}

t_uint64	ft_rotl_uint64(t_uint64 word, t_uint64 bits)
{
	return ((word << bits) | (word >> (64 - bits)));
}
