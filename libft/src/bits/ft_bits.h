/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bits.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 03:34:07 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/28 15:07:13 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BITS_H
# define FT_BITS_H

# include "../ft_libft_global.h"

# define SHOW(T,V) do { T x = V; ft_printb(#V, (unsigned char*) &x, sizeof(x)); } while(0)

/*
 *  INTEROPERABILITY
*/

typedef unsigned char t_uchar;

#ifdef __APPLE__

typedef uint8_t       t_uint8;
typedef uint16_t      t_uint16;
typedef uint32_t      t_uint32;
typedef uint64_t      t_uint64;

#endif
#ifdef __linux__

typedef uint8_t       t_uint8;
typedef uint16_t      t_uint16;
typedef uint32_t      t_uint32;
typedef uint64_t      t_uint64;

#endif


unsigned int ft_align_bits(size_t offset, size_t align);

void ft_printb_byte(char val);
void ft_printb(const char *var, unsigned char *bytes, size_t num_bytes);
void ft_printb_be(const char *var, unsigned char *bytes, size_t num_bytes);
void ft_printb_le(const char *var, unsigned char *bytes, size_t num_bytes);

uint32_t ft_rotl(uint32_t word, uint32_t bits);
uint32_t ft_rotr(uint32_t word, uint32_t bits);

uint32_t ft_rotr_uint32(uint32_t word, uint32_t bits);
uint32_t ft_rotl_uint32(uint32_t word, uint32_t bits);
uint32_t ft_shiftr_uint32(uint32_t word, uint32_t bits);
uint32_t ft_shiftl_uint32(uint32_t word, uint32_t bits);
uint32_t ft_swap_uint32(uint32_t *val);

uint64_t ft_rotr_uint64(uint64_t word, uint64_t bits);
uint64_t ft_rotl_uint64(uint64_t word, uint64_t bits);
uint64_t ft_shiftr_uint64(uint64_t word, uint64_t bits);
uint64_t ft_shiftl_uint64(uint64_t word, uint64_t bits);
uint64_t ft_swap_uint64(uint64_t *val);

#endif
