/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_res.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/28 16:59:49 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../ft_ping.h"

static int ft_ping_exec_finish_rtt(t_ping_res *stats) {
  double tsumTime = stats->sumTime / (double)stats->nbPcktReceive;
  double tsum2Time = stats->sum2Time / (double)stats->nbPcktReceive;
  double mdev = ft_sqrt(tsum2Time - (tsumTime * tsumTime));

  printf("rtt min/avg/max/mdev = ");
  printf("%0.3f/%0.3f/%0.3f/%0.3f ms", stats->minTime,
         stats->avgTime / stats->nbPcktReceive, stats->maxTime, mdev);

  return (FT_EXOK);
}

static int ft_ping_exec_finish_stats(const char *dest, t_ping_res *stats) {
  double nbPcktLoss = stats->nbPcktSend - stats->nbPcktReceive;
  double percentPcktLoss =
      stats->nbPcktSend ? nbPcktLoss / stats->nbPcktSend * 100 : 0;
  double time = ft_getelapsedtime(&stats->start);

  printf("\n--- %s ping statistics ---\n", dest);
  printf("%d packets transmitted, ", stats->nbPcktSend);
  printf("%d packets received, ", stats->nbPcktReceive);
  printf("%0.f%% packets packet loss, ", percentPcktLoss);
  printf("time %0.fms\n", time);

  return (FT_EXOK);
}

int ft_ping_res(t_ping_res stats, t_ping_opts opts) {
  ft_ping_exec_finish_stats(opts.dest, &stats);

  if (stats.nbPcktSend > 0 && stats.maxTime > 0 &&
      opts.packetsize >= (int)FT_TIMEVAL_LEN) {
    ft_ping_exec_finish_rtt(&stats);
  }

  printf("\n");

  return (FT_EXOK);
}
