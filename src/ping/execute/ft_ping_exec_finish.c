/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_finish.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/07/29 23:12:01 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../ft_ping.h"

static int ft_ping_exec_finish_rtt(t_pg_stats *stats) {
  double tsumTime;
  double tsum2Time;
  double mdev;

  tsumTime = stats->sumTime / (double)stats->nbPcktReceive;
  tsum2Time = stats->sum2Time / (double)stats->nbPcktReceive;
  mdev = ft_sqrt(tsum2Time - (tsumTime * tsumTime));

  printf("rtt min/avg/max/mdev = ");
  printf("%0.3f/%0.3f/%0.3f/%0.3f ms", stats->minTime,
         stats->avgTime / stats->nbPcktReceive, stats->maxTime, mdev);

  return (FT_EXOK);
}

static int ft_ping_exec_finish_stats(const char *dest, t_pg_stats *stats) {
  double nbPcktLoss;
  double percentPcktLoss;
  double time;

  nbPcktLoss = stats->nbPcktSend - stats->nbPcktReceive;
  percentPcktLoss =
      stats->nbPcktSend ? nbPcktLoss / stats->nbPcktSend * 100 : 0;
  time = ft_getelapsedtime(&stats->start);

  printf("\n--- %s ping statistics ---\n", dest);
  printf("%d packets transmitted, ", stats->nbPcktSend);
  printf("%d packets received, ", stats->nbPcktReceive);
  printf("%0.f%% packets packet loss, ", percentPcktLoss);
  printf("time %0.fms\n", time);

  return (FT_EXOK);
}

int ft_ping_exec_finish(t_ping *ctx) {
  ft_ping_exec_finish_stats(ctx->pg_opts.dest, &ctx->stats);

  if (ctx->stats.nbPcktSend > 0 && ctx->stats.maxTime > 0 &&
      ctx->pg_opts.packetsize >= FT_TIMEVAL_LEN) {
    ft_ping_exec_finish_rtt(&ctx->stats);
  }

  printf("\n");

  // free(sock->pckt_send.msg);
  // free(sock->pckt_recv.msg);
  // close(sock->fd);

  return (FT_EXOK);
}