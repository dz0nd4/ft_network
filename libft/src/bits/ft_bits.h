/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bits.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 17:42:12 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/03 13:05:01 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BITS_H
# define FT_BITS_H

# include <stdlib.h>

unsigned int	ft_align_bits(size_t offset, size_t align);

uint32_t		ft_rotr_uint32(uint32_t word, uint32_t bits);
uint32_t		ft_rotl_uint32(uint32_t word, uint32_t bits);
uint32_t		ft_shiftr_uint32(uint32_t word, uint32_t bits);
uint32_t		ft_shiftl_uint32(uint32_t word, uint32_t bits);
uint32_t		ft_swap_uint32(uint32_t *val);

uint64_t		ft_rotr_uint64(uint64_t word, uint64_t bits);
uint64_t		ft_rotl_uint64(uint64_t word, uint64_t bits);
uint64_t		ft_shiftr_uint64(uint64_t word, uint64_t bits);
uint64_t		ft_shiftl_uint64(uint64_t word, uint64_t bits);
uint64_t		ft_swap_uint64(uint64_t *val);

#endif
