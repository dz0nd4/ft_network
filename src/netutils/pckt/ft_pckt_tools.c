/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pckt_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/28 13:31:25 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pckt.h"

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
  long sum = 0;

  while (len > 1) {
    sum += *buf++;
    len -= 2;
  }
  if (len > 0) sum += *(unsigned char *)buf;

  while (sum >> 16) sum = (sum & 0xffff) + (sum >> 16);

  return ((unsigned short)~sum);
}

/*
 * ft_pckt_random_data
 *
 * Description:
 *   Fill packet with random data
 * Returns:
 *   FT_EXOK or FT_EXFAIL if ft_inet_ntop fails
 */
t_uchar *ft_pckt_random_data(t_uchar *data, t_uint16 len) {
  t_uint16 i = 0;

  while (i < len) {
    data[i] = i + '0';
    i += 1;
  }
  data[i] = 0;

  return (data);
}

/*
 * ft_pckt_set_time
 *
 * Description:
 *   Set the time in a packet
 * Returns:
 *   FT_EXOK or FT_EXFAIL if ft_inet_ntop fails
 */
void ft_pckt_set_time(t_uchar *data) {
  t_timeval tv;

  ft_memset(&tv, 0, sizeof(tv));
  ft_gettimeofday(&tv);
  ft_memcpy(data, &tv, sizeof(tv));
}
