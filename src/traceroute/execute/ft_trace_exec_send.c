/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace_execute_send.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 15:02:40 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

/*
 * ft_trace_exec_send
 *
 * Description:
 *    Send probe with custom TTL
 * Returns:
 *    The number data send
 */
int ft_trace_exec_send(t_tr_opts *opts, t_tr_sock *to) {
  t_pckt pckt;
  t_pckt_opt opt;
  int i;

  pckt.len = opts->packetlen & FT_UINT16_MAX;
  if ((pckt.data = (t_uchar *)ft_memalloc(pckt.len)) == NULL)
    return (FT_EXFAIL);

  // opt.ttl = opts->hops;
  // opt.port = htons(opts->port + opts->hops + opts->probes);
  // opt.proto = IPPROTO_UDP;

  ft_memset(&opt, 0, sizeof(opt));

  ft_pckt_ip_opt_default(&opt.ip);
  ft_pckt_udp_opt_default(&opt.udp);

  opt.ip.len = pckt.len;
  opt.ip.proto = IPPROTO_UDP;
  opt.ip.ttl = opts->hops;
  opt.ip.daddr = to->saddrin.sin_addr.s_addr;

  opt.udp.len = pckt.len - FT_IPHDR_LEN;
  opt.udp.dport = opts->port + opts->hops + opts->probes;

  ft_pckt_ip_opt_set(&pckt, &opt.ip);
  ft_pckt_udp_opt_set(&pckt, &opt.udp);

  i = ft_sendto(to->fd, pckt.data, pckt.len, &to->saddrin);

  return (i);
}
