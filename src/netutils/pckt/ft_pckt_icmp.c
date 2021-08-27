/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pckt_icmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/12 09:36:45 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_sock.h"

/*
 * ft_pckt_icmp_opt_default
 *
 * Description:
 *    Initialize ICMP options header
 * Returns:
 *
 */
void ft_pckt_icmp_opt_default(t_pckt_icmp *opt) {
  ft_memset(opt, 0, sizeof(*opt));

  opt->id = (getpid() & FT_UINT16_MAX);
  opt->type = ICMP_ECHO;
}

/*
 * ft_pckt_icmp_opt_set
 *
 * Description:
 *    Set ICMP options header
 * Returns:
 *
 */
void ft_pckt_icmp_opt_set(t_pckt *pckt, t_pckt_icmp *opts) {
  t_icmphdr *icmp = NULL;

  if (pckt == NULL || pckt->data == NULL || pckt->len == 0 || opts == NULL)
    return;

  icmp = (t_icmphdr *)&pckt->data[FT_IPHDR_LEN];

  icmp->type = opts->type;
  icmp->un.echo.id = opts->id;
  icmp->un.echo.sequence = opts->seq;
  icmp->checksum = 0;

  if ((pckt->len - FT_PING_HDR) >= FT_TIMEVAL_LEN) {
    ft_pckt_set_time(&pckt->data[FT_PING_HDR]);
  }

  icmp->checksum =
      ft_checksum(&pckt->data[FT_IPHDR_LEN], (pckt->len - FT_IPHDR_LEN));
}
