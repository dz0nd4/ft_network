/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 17:41:54 by dzonda            #+#    #+#             */
/*   Updated: 2021/06/10 15:54:12 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bits.h"

uint32_t	ft_rotl(uint32_t word, uint32_t bits)
{
	return (ft_rotl_uint32(word, bits));
}

uint32_t	ft_rotr(uint32_t word, uint32_t bits)
{
	return (ft_rotr_uint32(word, bits));
}

uint32_t	ft_rotr_uint32(uint32_t word, uint32_t bits)
{
	return ((word >> bits) | (word << (32 - bits)));
}

uint32_t	ft_rotl_uint32(uint32_t word, uint32_t bits)
{
	return ((word << bits) | (word >> (32 - bits)));
}

uint64_t	ft_rotr_uint64(uint64_t word, uint64_t bits)
{
	return ((word >> bits) | (word << (64 - bits)));
}

uint64_t	ft_rotl_uint64(uint64_t word, uint64_t bits)
{
	return ((word << bits) | (word >> (64 - bits)));
}
