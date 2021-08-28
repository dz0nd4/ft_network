/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_recv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/27 16:25:29 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

/*
 * ft_ping_exec_print_addr
 *
 * Description:
 *   Print the address from received packet
 * Returns:
 *   FT_EXOK or FT_EXFAIL if ft_inet_ntop fails
 */
int ft_ping_exec_print_addr(t_sockaddr_in *addrin, int numeric_only) {
  char ipv4[FT_ADDRSTRLEN];
  char hostname[FT_NI_MAXHOST];

  ft_bzero(ipv4, FT_ADDRSTRLEN);
  ft_bzero(hostname, FT_NI_MAXHOST);

  if (ft_inet_ntop((t_in_addr *)&addrin->sin_addr, ipv4) == FT_EXFAIL)
    return (FT_EXFAIL);

  if (!numeric_only) {
    if (ft_getnameinfo(addrin, hostname) == FT_EXFAIL) return (FT_EXFAIL);

    printf("%s (%s): ", hostname, ipv4);
  } else {
    printf("%s: ", ipv4);
  }

  return (FT_EXOK);
}

int ft_ping_exec_recv_pckt_false(t_pckt pckt, t_pg_opts opts) {
  t_icmphdr *icmp = (t_icmphdr *)&pckt.data[FT_IPHDR_LEN];
  char hostname[FT_NI_MAXHOST];
  ft_bzero(hostname, FT_NI_MAXHOST);

  opts.numeric_only
      ? printf("From %s: icmp_seq=%u ", inet_ntoa(pckt.to.sin_addr),
               icmp->un.echo.sequence)
      : printf("From %s (%s): icmp_seq=%u ",
               ft_getnameinfo_pr(&pckt.to, hostname),
               inet_ntoa(pckt.to.sin_addr), icmp->un.echo.sequence);

  if (opts.verbose) {
    printf("icmp_type=%u %s icmp_code=%u ", icmp->type,
           ft_pckt_icmp_type(icmp->type), icmp->code);
    if (icmp->type == ICMP_DEST_UNREACH)
      printf("%s\n", ft_pckt_icmp_code_unreach(icmp->code));
    if (icmp->type == ICMP_REDIRECT)
      printf("%s\n", ft_pckt_icmp_code_redir(icmp->code));
    if (icmp->type == ICMP_TIME_EXCEEDED)
      printf("%s\n", ft_pckt_icmp_code_exc(icmp->code));
  } else {
    printf("%s\n", ft_pckt_icmp_type(icmp->type));
  }

  return (FT_EXOK);
}

int ft_ping_exec_recv_pckt_reply(t_pckt pckt, t_pg_opts opts,
                                 t_pg_stats *stats) {
  t_iphdr *ip = (t_iphdr *)&pckt.data[0];
  t_icmphdr *icmp = (t_icmphdr *)&pckt.data[FT_IPHDR_LEN];
  t_timeval *tv = (t_timeval *)&pckt.data[FT_PING_HDR];
  double elapsed_time = 0;

  printf("%ld bytes from ", pckt.cc - FT_IPHDR_LEN);
  ft_ping_exec_print_addr(&pckt.to, opts.numeric_only);
  printf("icmp_seq=%u ttl=%d ", icmp->un.echo.sequence, ip->ttl);

  if (opts.packetsize >= (int)FT_TIMEVAL_LEN) {
    elapsed_time = ft_getelapsedtime(tv);

    if (stats->minTime == 0 || elapsed_time < stats->minTime)
      stats->minTime = elapsed_time;
    if (elapsed_time > stats->maxTime) stats->maxTime = elapsed_time;

    stats->avgTime += elapsed_time;
    stats->sumTime += elapsed_time;
    stats->sum2Time += elapsed_time * elapsed_time;

    printf("time=%0.2f ms", elapsed_time);
  }

  printf("\n");

  return (FT_EXOK);
}

/*
 * ft_ping_exec_recv
 *
 * Description:
 *   Clear msg pckt_recv and receive new packet
 * Returns:
 *   FT_EXOK or FT_EXFAIL if ft_recvmsg fails
 */
int ft_ping_exec_recv(t_ping *ctx) {
  t_pckt pckt;

  ft_memset(&pckt, 0, sizeof(pckt));

  pckt.len = (FT_PING_HDR + ctx->pg_opts.packetsize) & FT_UINT16_MAX;
  if ((pckt.data = (t_uchar *)ft_memalloc(pckt.len)) == NULL)
    return (FT_EXFAIL);

  // t_iphdr *iphdr = (t_iphdr *)&pckt.data[0];
  t_icmphdr *icmphdr = (t_icmphdr *)&pckt.data[FT_IPHDR_LEN];
  // t_timeval *tv = (t_timeval *)&pckt.data[FT_PING_HDR];

  pckt.cc = ft_recvmsg(ctx->fd, (char *)&pckt.to, (char *)pckt.data, pckt.len);
  if (pckt.cc < 0) return (FT_EXFAIL);

  if (icmphdr->type != ICMP_ECHOREPLY) {
    ft_ping_exec_recv_pckt_false(pckt, ctx->pg_opts);
  } else if (icmphdr->un.echo.id == ctx->id) {
    ft_ping_exec_recv_pckt_reply(pckt, ctx->pg_opts, &ctx->stats);
  }

  free(pckt.data);
  ctx->stats.nbPcktReceive += 1;

  return (FT_EXOK);
}
