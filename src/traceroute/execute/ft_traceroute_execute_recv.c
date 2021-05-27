/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_execute_recv.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/27 01:00:48 by dzonda           ###   ########lyon.fr   */
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

  t_tr_pack_hdr_icmp *hdr_icmp; 
  t_tr_pack_hdr_udp *hdr_udp;

    hdr_icmp = (t_tr_pack_hdr_icmp *)ctx->from.buffer;
  hdr_udp = (t_tr_pack_hdr_udp *)&hdr_icmp->icmp.icmp_ip;
  // if (ctx->opts.probes == 0) {
  //   printf(" %d", ctx->opts.hops);
    host_addr = inet_ntoa(ctx->from.saddrin.sin_addr);

  if (!ft_strequ(ctx->from.ip_last, host_addr)) {
    ft_strcpy(ctx->from.ip_last, host_addr);

    ft_tr_resolve(&ctx->from.saddrin, host_name);
    // host_addr = inet_ntoa(ctx->from.saddrin.sin_addr);
    printf("  %s (%s)", host_name, host_addr);
  }

  if (ctx->from.cc == 0) {
    printf("  *");
  } else {
    // printf("  %0.2f ms", ft_traceroute_execute_recv_print_time(&ctx->time));
  }

  if (ctx->opts.probes + 1 >= ctx->opts.probes_max)
    printf("\n");
}

int   ft_traceroute_execute_recv(t_trace *ctx, char *buffer, t_tr_from *from)
{
    fd_set    fds;
int cc;

  char buff[BUF_SIZE];
  t_tr_pack_hdr_icmp *hdr_icmp; 
  t_tr_pack_hdr_udp *hdr_udp;
			from->cc = 0;
			ft_memset(from->buffer, 0, BUF_SIZE);
  		ft_memset(&from->saddrin, 0, sizeof(t_sockaddr_in));
  // ft_memset(from->buffer, 0, BUF_SIZE);
  // ft_memset(&from->saddrin, 0, sizeof(t_sockaddr_in));
  hdr_icmp = (t_tr_pack_hdr_icmp *)buffer;
  hdr_udp = (t_tr_pack_hdr_udp *)&hdr_icmp->icmp.icmp_ip;
  // from->cc = 0;

				FD_ZERO(&fds);

				FD_SET(from->sfd, &fds);
  gettimeofday(&ctx->time.stop, NULL);
  if (select(from->sfd + 1, &fds, (fd_set *)0, (fd_set *)0, &from->wait))
    from->cc = ft_sock_recv(from->sfd, from->buffer, BUF_SIZE, &from->saddrin);
  // }

  // if (hdr_udp->udp.uh_sport == htons(getpid()))
  //   ft_traceroute_execute_recv_print(ctx);
  // else {
  //   printf(" *");
  // }
  ctx->from.code = hdr_icmp->icmp.icmp_code;
  return (from->cc);
}
