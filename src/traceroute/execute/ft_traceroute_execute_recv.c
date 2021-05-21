/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_execute_recv.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 15:01:33 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

static double   ft_traceroute_execute_recv_print_time(t_tr_time *time)
{
  double start = (time->start.tv_sec) * 1000 + (time->start.tv_usec) / 1000;
  double stop = (time->stop.tv_sec) * 1000 + (time->stop.tv_usec) / 1000 ;
  double dt = stop - start;
  return dt;
}

int   ft_traceroute_execute_recv_print(t_trace *ctx)
{
  char host_name[FT_NI_MAXHOST];
  char *host_addr;


  if (ctx->opts.probes == 0) {
    printf(" %d", ctx->opts.hops);

  // if (!ft_strequal(ctx->from.ip_last, str)) {
  //   ft_strcpy(ctx->from.ip_last, str);

    ft_tr_resolve(&ctx->from.saddrin, host_name);
    host_addr = inet_ntoa(ctx->from.saddrin.sin_addr);
    printf("  %s (%s)", host_name, host_addr);
  }

  if (ctx->from.cc == 0) {
    printf("  *");
  } else {
    printf("  %0.2f ms", ft_traceroute_execute_recv_print_time(&ctx->time));
  }

  if (ctx->opts.probes + 1 >= ctx->opts.probes_max)
    printf("\n");
}

int   ft_traceroute_execute_recv(t_trace *ctx, char *buffer, t_tr_from *from)
{
  char buff[BUF_SIZE];
  t_tr_pack_hdr_icmp *hdr_icmp; 
  t_tr_pack_hdr_udp *hdr_udp;

  ft_memset(buff, 0, BUF_SIZE);
  hdr_icmp = (t_tr_pack_hdr_icmp *)buffer;
  hdr_udp = (t_tr_pack_hdr_udp *)&hdr_icmp->icmp.icmp_ip;

  gettimeofday(&ctx->time.stop, NULL);
  from->cc = ft_sock_recv(from->sfd, &from->buffer, BUF_SIZE, &from->saddrin);

  if (hdr_udp->udp.uh_sport == htons(getpid()))
    ft_traceroute_execute_recv_print(ctx);

  ctx->from.code = hdr_icmp->icmp.icmp_code;
  return (EXIT_FAILURE);
}
