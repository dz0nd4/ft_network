/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:08:57 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/12 16:59:30 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_to.h"

uint64_t ft_hextoi(char *hex) {
  uint64_t val = 0;
  while (*hex) {
    // get current character then increment
    uint8_t byte = *hex++;
    // transform hex character to the 4bit equivalent number, using the ascii
    // table indexes
    if (byte >= '0' && byte <= '9')
      val = (val << 4) | ((byte - 48) & 0xF);
    else if (byte >= 'A' && byte <= 'F')
      val = (val << 4) | ((byte - 55) & 0xF);
    else if (byte >= 'a' && byte <= 'f')
      val = (val << 4) | ((byte - 87) & 0xF);
    else
      return 0;
  }
  // return val;
  return (ft_swap_uint64(&val));
}