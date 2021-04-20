/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_exec_send.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/20 16:38:54 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

int   ft_traceroute_exec_send(t_trace *ctx)
{
  t_sockaddr_in to;
  struct timeval tv;
  char buffer[32];
  int port = 33435;

  ft_bzero(buffer, 32);
  ft_strcpy(buffer, "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_");

  ft_memset(&to, 0, sizeof(to));
	to.sin_family = AF_INET;
  to.sin_port = htons(port + ctx->opts.hops + ctx->opts.probes);
	to.sin_addr.s_addr = inet_addr(ctx->host.ip);

  gettimeofday(&ctx->tv, NULL);

  if (setsockopt(ctx->sock.udp, IPPROTO_IP, IP_TTL, &ctx->opts.hops, sizeof(ctx->opts.hops)) < 0)
		ft_exit("setsockopt()");

	t_ip *ip = &ctx->sock.udp_pack.ip;
  t_udp *udp = &ctx->sock.udp_pack.udp;

  ip->ip_dst = to.sin_addr;
	ip->ip_ttl = ctx->opts.hops;

	udp->uh_dport = htons(ctx->opts.port + ctx->opts.hops + ctx->opts.probes);


  int i = 0;
  if ((i = sendto(ctx->sock.udp, (char *)&ctx->sock.udp_pack, sizeof(t_tr_pack), 0, (t_sockaddr *)&to, sizeof(t_sockaddr))) < 0)
		ft_exit("sendto()");

  return (EXIT_SUCCESS);
}
