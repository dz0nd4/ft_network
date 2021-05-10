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

# if __APPLE__
  typedef uint32_t  t_uint32;
  typedef uint64_t  t_uint64;
#elif __linux__
  typedef u_int32_t  t_uint32;
  typedef u_int64_t  t_uint64;
#endif

unsigned int	ft_align_bits(size_t offset, size_t align);

t_uint32		ft_rotr_uint32(t_uint32 word, t_uint32 bits);
t_uint32		ft_rotl_uint32(t_uint32 word, t_uint32 bits);
t_uint32		ft_shiftr_uint32(t_uint32 word, t_uint32 bits);
t_uint32		ft_shiftl_uint32(t_uint32 word, t_uint32 bits);
t_uint32		ft_swap_uint32(t_uint32 *val);

t_uint64		ft_rotr_uint64(t_uint64 word, t_uint64 bits);
t_uint64		ft_rotl_uint64(t_uint64 word, t_uint64 bits);
t_uint64		ft_shiftr_uint64(t_uint64 word, t_uint64 bits);
t_uint64		ft_shiftl_uint64(t_uint64 word, t_uint64 bits);
t_uint64		ft_swap_uint64(t_uint64 *val);

#endif
