/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shift.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 17:46:01 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:11:07 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bits.h"

uint32_t	ft_shiftr_uint32(uint32_t word, uint32_t bits)
{
	return (word >> bits);
}

uint32_t	ft_shiftl_uint32(uint32_t word, uint32_t bits)
{
	return (word << bits);
}

uint64_t	ft_shiftr_uint64(uint64_t word, uint64_t bits)
{
	return (word >> bits);
}

uint64_t	ft_shiftl_uint64(uint64_t word, uint64_t bits)
{
	return (word << bits);
}
