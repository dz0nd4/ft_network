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

t_uint32	ft_shiftr_uint32(t_uint32 word, t_uint32 bits)
{
	return (word >> bits);
}

t_uint32	ft_shiftl_uint32(t_uint32 word, t_uint32 bits)
{
	return (word << bits);
}

t_uint64	ft_shiftr_uint64(t_uint64 word, t_uint64 bits)
{
	return (word >> bits);
}

t_uint64	ft_shiftl_uint64(t_uint64 word, t_uint64 bits)
{
	return (word << bits);
}
