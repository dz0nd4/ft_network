/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 17:41:54 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/09 09:11:04 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bits.h"

void ft_set_bit(t_uint8 *dst, int index, int value) {
  int cell = index / 8;
  int bit = 7 - index % 8;
  if (value == 0) {
    dst[cell] &= ~(1 << bit);
  } else {
    dst[cell] |= (1 << bit);
  }
}

int ft_get_bit(const t_uint8 *src, int index) {
  int cell = index / 8;
  int bit = 7 - index % 8;
  return (src[cell] & (1 << bit)) != 0;
}
