/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/26 18:28:40 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <poll.h>
#include <signal.h>

#include "ft_nmap.h"

int ft_getaddrin_raw(t_sockaddr_in *in, char *ip) {
  t_addrinfo addr;

  ft_memset(&addr, 0, sizeof(addr));
  addr.ai_family = AF_INET;
  addr.ai_socktype = SOCK_RAW;
  addr.ai_protocol = IPPROTO_RAW;

  if (ft_getaddrinfo((const char *)ip, &addr) == FT_EXOK) {
    ft_memcpy(in, addr.ai_addr, sizeof(addr.ai_addr));
    return (FT_EXOK);
  }

  return (FT_EXFAIL);
}

int ft_nmap_exec_thr_wait(t_nmap_thr threads[FT_NMAP_THREADS_MAX],
                          int *nthreads, int speedup) {
  int i = -1;

  while (++i < speedup) {
    if (threads[i].lock = 1) {
      if ((pthread_join(threads[i].fd, NULL)) == 0) {
        threads[i].lock = 0;
        *nthreads -= 1;
      } else {
        perror("pthread_join");
        return (FT_EXFAIL);
      }
    }
  }
  return (FT_EXOK);
}

int ft_nmap_exec_thr(void *arg) {
  t_nmap_resps *resps = (t_nmap_resps *)arg;

  // fprintf(stdout, "Scanning port %d..\n", resp->port);

  ft_nmap_exec_recv3(resps);
  return (FT_EXOK);  // pthread_exit(FT_EXOK);
}

int ft_nmap_exec_thr_create(t_nmap_mthr *mthr, t_nmap_resps *resps) {
  if (pthread_create(&mthr->thr[mthr->ithr].fd, NULL, ft_nmap_exec_thr,
                     resps) == FT_EXOK) {
    mthr->thr[mthr->ithr].lock = 1;
    mthr->ithr += 1;
  } else {
    perror("pthread_create");
    return (FT_EXFAIL);
  }
  return (FT_EXOK);
}

int ft_nmap_exec2_init(t_nmap_ctx *ctx, t_nmap_opts *opts) {
  t_nmap_resp *resp = NULL;
  t_nmap_resps *resps = NULL;

  /* Initialize result_port */
  resp = &ctx->resp[ctx->iport];
  resp->port = opts->ports[ctx->iport];
  resp->scan = opts->scan;

  /* Initialize result_port_scan */
  resps = &resp->res_scan[ctx->iscan];
  resps->key = 1 << ctx->iscan;
  resps->ip = ctx->ip;
  resps->port = opts->ports[ctx->iport];

  return (FT_EXOK);
}

int ft_nmap_exec2(t_nmap_ctx *ctx, t_nmap_opts *opts) {
  t_nmap_mthr mthr = {0};
  int i = -1;

  while (++i < opts->nip) {
    /* Initialize context */
    ft_memcpy(ctx->ip, opts->ip[i], 256);
    ft_memset(&mthr, 0, sizeof(mthr));

    ctx->iport = 0;
    while (ctx->iport < opts->nports) {
      ctx->iscan = -1;

      while (++(ctx->iscan) < FT_NMAP_SCAN_MAX) {
        if (opts->scan & (1 << ctx->iscan)) {
          ft_nmap_exec2_init(ctx, opts);

          if (mthr.ithr == opts->speedup)
            ft_nmap_exec_thr_wait(mthr.thr, &mthr.ithr, opts->speedup);

          ft_nmap_exec_thr_create(&mthr,
                                  &ctx->resp[ctx->iport].res_scan[ctx->iscan]);
        }
      }
      ctx->iport += 1;
    }

    if (mthr.ithr != 0)
      ft_nmap_exec_thr_wait(mthr.thr, &mthr.ithr, opts->speedup);

    ft_nmap_result2(*ctx, *opts);
  }
  return (FT_EXOK);
}