/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_send.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/07/30 14:09:10 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

/*
 * ft_ping_exec_send
 *
 * Description:
 *   Modify header of pckt_send: sequence, timeval & checksum
 * Returns:
 *   FT_EXOK or FT_EXFAIL if ft_sendto fails
 */
int ft_ping_exec_send(t_ping *ctx) {
  t_pckt pckt;
  t_pckt_opt opt;

  ft_memset(&pckt, 0, sizeof(pckt));
  ft_memset(&opt, 0, sizeof(opt));

  pckt.len = (FT_PING_HDR + ctx->pg_opts.packetsize) & FT_UINT16_MAX;
  pckt.to = ctx->to;
  if ((pckt.data = (t_uchar *)ft_memalloc(pckt.len)) == NULL)
    return (FT_EXFAIL);

  ft_pckt_ip_opt_default(&opt.ip);
  ft_pckt_icmp_opt_default(&opt.icmp);

  opt.ip.len = pckt.len;
  opt.ip.proto = IPPROTO_ICMP;
  opt.ip.ttl = ctx->pg_opts.ttl;
  opt.ip.daddr = ctx->to.sin_addr.s_addr;

  opt.icmp.seq = (ctx->stats.nbPcktSend + 1) & FT_UINT16_MAX;

  ft_pckt_ip_opt_set(&pckt, &opt.ip);
  ft_pckt_icmp_opt_set(&pckt, &opt.icmp);

  if (ft_sendto(ctx->fd, pckt.data, pckt.len, &ctx->to) == FT_EXFAIL)
    return (FT_EXFAIL);

  free(pckt.data);
  ctx->stats.nbPcktSend += 1;

  return (FT_EXOK);
}
