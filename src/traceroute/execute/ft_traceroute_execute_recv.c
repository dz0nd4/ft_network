/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_execute_recv.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/10 15:18:02 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

int   ft_traceroute_execute_recv_print(t_trace *ctx)
{
  char str[FT_ADDRSTRLEN];
  char *tmp = inet_ntoa(ctx->from.saddrin.sin_addr);
  ft_strcpy(str, tmp);

  double start = (ctx->time.start.tv_sec) * 1000 + (ctx->time.start.tv_usec) / 1000;
  double stop = (ctx->time.stop.tv_sec) * 1000 + (ctx->time.stop.tv_usec) / 1000 ;
  double dt = stop - start;

  if (ctx->opts.probes == 0)
    printf("\n %d", ctx->opts.hops);

  if (!ft_strequal(ctx->from.ip_last, str)) {
    ft_strcpy(ctx->from.ip_last, str);

    char name[NI_MAXHOST];
    ft_tr_resolve(&ctx->from.saddrin, name);

    printf("  %s (%s)", name, ctx->from.ip_last);
  }

  if (ctx->from.cc == 0) {
    printf("  *");
  } else {
    printf("  %0.2f ms", dt);
  }
}

int   ft_traceroute_execute_recv_check(t_trace *ctx, char *buffer)
{
  t_tr_pack_hdr_icmp *hdr_icmp; 
  t_tr_pack_hdr_udp *hdr_udp;
  char type;
  char code;
  
  hdr_icmp = (t_tr_pack_hdr_icmp *)buffer;
  type = hdr_icmp->icmp.icmp_type;
  code = hdr_icmp->icmp.icmp_code;
  ctx->from.code = code;

  hdr_udp = (t_tr_pack_hdr_udp *)&hdr_icmp->icmp.icmp_ip;

  if (hdr_udp->udp.uh_sport != htons(getpid()))
    return (EXIT_FAILURE);

  return (EXIT_SUCCESS);
}

int   ft_traceroute_execute_recv(t_trace *ctx, char *buffer, t_tr_from *from)
{
  gettimeofday(&ctx->time.stop, NULL);
  from->cc = ft_socket_recv(from->sfd, &from->buffer, BUF_SIZE, &from->saddrin);

  if (ft_traceroute_execute_recv_check(ctx, &ctx->from.buffer) == EXIT_SUCCESS) {
    ft_traceroute_execute_recv_print(ctx);
  }
  return (EXIT_FAILURE);
}
