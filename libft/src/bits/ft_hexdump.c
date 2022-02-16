/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 17:41:54 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/09 09:15:09 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bits.h"

void ft_hexdump(void *mem, unsigned int len) {
  unsigned int i, j;

  for (i = 0;
       i <
       len + ((len % HEXDUMP_COLS) ? (HEXDUMP_COLS - len % HEXDUMP_COLS) : 0);
       i++) {
    /* print offset */
    if (i % HEXDUMP_COLS == 0) {
      printf("0x%06x: ", i);
    }

    /* print hex data */
    if (i < len) {
      printf("%02x ", 0xFF & ((char *)mem)[i]);
    } else /* end of block, just aligning for ASCII dump */
    {
      printf("   ");
    }

    /* print ASCII dump */
    if (i % HEXDUMP_COLS == (HEXDUMP_COLS - 1)) {
      for (j = i - (HEXDUMP_COLS - 1); j <= i; j++) {
        if (j >= len) /* end of block, not really printing */
        {
          putchar(' ');
        } else if (isprint(((char *)mem)[j])) /* printable char */
        {
          putchar(0xFF & ((char *)mem)[j]);
        } else /* other char */
        {
          putchar('.');
        }
      }
      putchar('\n');
    }
  }
}