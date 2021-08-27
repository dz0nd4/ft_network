/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/07/30 14:08:48 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int ft_ping_exec_init2(t_ping *ctx) {
  t_addrinfo addr;

  ft_memset(&addr, 0, sizeof(t_addrinfo));
  addr.ai_family = AF_INET;
  addr.ai_socktype = SOCK_DGRAM;
  // addr.ai_protocol = IPPROTO_ICMP;

  if (ft_getaddrinfo(ctx->pg_opts.dest, &addr) == FT_EXFAIL)
    return (ft_getnameinfo_err("ft_ping: ", ctx->pg_opts.dest));

  ctx->fd = socket(addr.ai_family, addr.ai_socktype, IPPROTO_ICMP);

  if (ctx->fd == INVALID_SOCKET) {
    if (ctx->pg_opts.verbose)
      fprintf(stderr, "ft_ping: Permission denied, attempting raw socket...\n");

    ft_memset(&addr, 0, sizeof(t_addrinfo));
    addr.ai_family = AF_INET;
    addr.ai_socktype = SOCK_RAW;
    addr.ai_protocol = IPPROTO_ICMP;

    if (ft_getaddrinfo(ctx->pg_opts.dest, &addr) == FT_EXFAIL)
      return (ft_getnameinfo_err("ft_ping: ", ctx->pg_opts.dest));

    // pckt->fd = socket(addr.ai_family, addr.ai_socktype, IPPROTO_ICMP);
    ctx->fd = ft_socket_icmp();
    if (ctx->fd == INVALID_SOCKET) {
      fprintf(stderr, "ping: socket: Permission denied for raw socket\n");
      return (FT_EXFAIL);
    }
  }

  ctx->id = getpid() & FT_UINT16_MAX;
  // pckt->len = (FT_PING_HDR + opts.packetsize) & FT_UINT16_MAX;
  ft_memcpy(&ctx->to, addr.ai_addr, sizeof(t_sockaddr));
  ft_setsockopt_sndtimeo(&ctx->fd, 1, ctx->pg_opts.verbose);
  ft_setsockopt_rcvtimeo(&ctx->fd, 1, ctx->pg_opts.verbose);
  return (FT_EXOK);
  // if ((pckt->data = ft_memalloc(pckt->len)) == NULL) return (FT_EXFAIL);
}

int ft_ping_execute(t_pg_opts opts) {
  t_pckt pckt;
  t_pg_stats stats;

  t_ping ctx;

  ft_memset(&ctx, 0, sizeof(ctx));

  ctx.pg_opts = opts;

  ft_memset(&pckt, 0, sizeof(pckt));
  ft_memset(&stats, 0, sizeof(stats));

  // if (ft_ping_exec_init(opts, &sock, &stats) == FT_EXFAIL) return
  // (FT_EXFAIL);
  if (ft_ping_exec_init2(&ctx) == FT_EXFAIL) return (FT_EXFAIL);

  signal(SIGINT, ft_ping_sigint);
  signal(SIGALRM, ft_ping_sigarlm);

  alarm(FT_PING_DEFAULT_DELAY);

  printf("PING %s (%s) %d(%ld) bytes of data.\n", opts.dest,
         inet_ntoa(ctx.to.sin_addr), opts.packetsize,
         opts.packetsize + FT_PING_HDR);

  ft_gettimeofday(&ctx.stats.start);
  while (g_ping >= FT_PING_RUN) {
    if (g_ping == FT_PING_SEND) {
      if (ft_ping_exec_send(&ctx) == FT_EXFAIL) break;
      if (g_ping != FT_PING_STOP) g_ping = FT_PING_RUN;
    }
    ft_ping_exec_recv(&ctx);
  }

  ft_ping_exec_finish(&ctx);

  return (FT_EXOK);
}
