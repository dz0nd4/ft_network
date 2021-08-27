/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sock_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/07/26 23:31:19 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_sock.h"

/*
 * ft_checksum
 *
 * Description:
 *    One's complement function
 * Returns:
 *
 */
unsigned short ft_checksum(void *b, int len) {
  unsigned short *buf = b;
  //   unsigned int sum = 0;

  //   for (sum = 0; len > 1; len -= 2) sum += *buf++;
  //   if (len == 1) sum += *(unsigned char *)buf;
  //   sum = (sum >> 16) + (sum & 0xFFFF);
  //   sum += (sum >> 16);
  /* Compute Internet Checksum for "count" bytes
   *         beginning at location "addr".
   */
  register long sum = 0;

  while (len > 1) {
    /*  This is the inner loop */
    sum += *buf++;
    len -= 2;
  }

  /*  Add left-over byte, if any */
  if (len > 0) sum += *(unsigned char *)buf;

  /*  Fold 32-bit sum to 16 bits */
  while (sum >> 16) sum = (sum & 0xffff) + (sum >> 16);

  return ((unsigned short)~sum);
}

#ifndef HEXDUMP_COLS
#define HEXDUMP_COLS 16
#endif

void hexdump(void *mem, unsigned int len) {
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
