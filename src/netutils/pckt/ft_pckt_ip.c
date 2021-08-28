/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pckt_ip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/27 17:02:57 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pckt.h"

/*
 * ft_pckt_ip_opt_default
 *
 * Description:
 *    Initialize IP options header
 * Returns:
 *
 */
void ft_pckt_ip_opt_default(t_pckt_ip *opts) {
  ft_memset(opts, 0, sizeof(*opts));

  opts->ihl = FT_IPIHL;
  opts->ver = FT_IPVERSION;
  opts->id = (getpid() & FT_UINT16_MAX);
  opts->ttl = 64;
}

/*
 * ft_pckt_ip_opt_set
 *
 * Description:
 *    Set IP options header
 * Returns:
 *
 */
void ft_pckt_ip_opt_set(t_pckt *pckt, t_pckt_ip *opts) {
  t_iphdr *ip = NULL;

  if (pckt == NULL || pckt->data == NULL || pckt->len == 0 || opts == NULL)
    return;

  ip = (t_iphdr *)&pckt->data[0];

  ip->ihl = opts->ihl;
  ip->version = opts->ver;
  ip->tot_len = opts->len;
  ip->id = opts->id;
  ip->protocol = opts->proto;
  ip->ttl = opts->ttl;
  ip->daddr = opts->daddr;
}
