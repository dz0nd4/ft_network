/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pckt_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/07/28 13:54:12 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_sock.h"

/*
 Checksums - IP and TCP
 */
unsigned short csum(unsigned short *ptr, int nbytes) {
  register long sum;
  unsigned short oddbyte;
  register short answer;

  sum = 0;
  while (nbytes > 1) {
    sum += *ptr++;
    nbytes -= 2;
  }
  if (nbytes == 1) {
    oddbyte = 0;
    *((u_char *)&oddbyte) = *(u_char *)ptr;
    sum += oddbyte;
  }

  sum = (sum >> 16) + (sum & 0xffff);
  sum = sum + (sum >> 16);
  answer = (short)~sum;

  return (answer);
}

t_uchar *ft_pckt_random_data(t_uchar *data, t_uint16 len) {
  t_uint16 i = 0;

  while (i < len) {
    data[i++] = i + '0';
  }
  data[i] = 0;

  return (data);
}

void ft_pckt_set_time(t_uchar *data) {
  t_timeval tv;

  ft_memset(&tv, 0, sizeof(tv));
  ft_gettimeofday(&tv);
  ft_memcpy(data, &tv, sizeof(tv));
}