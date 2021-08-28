/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/28 17:00:07 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int g_ping = FT_PING_RUN;

void ft_ping_sigint() { g_ping = FT_PING_STOP; }

void ft_ping_sigarlm() {
  if (g_ping != FT_PING_STOP) {
    g_ping = FT_PING_SEND;
    alarm(FT_PING_DEFAULT_DELAY);
  }
}

int ft_ping_usage() {
  fprintf(stderr, "Usage: ping [-hnv] ");
  fprintf(stderr, "[-s packetsize] [-t ttl] destination\n");
  return (FT_EXFAIL);
}

int ft_ping_init(t_ping_opts *opts) {
  opts->ttl = FT_PING_TTL_DEFAULT;
  opts->packetsize = FT_PING_PACKETSIZE_DEFAULT;

  return (FT_EXOK);
}

int ft_ping(int argc, const char *argv[]) {
  t_ping_opts opts;
  t_ping_res res;

  ft_memset(&opts, 0, sizeof(opts));
  ft_memset(&res, 0, sizeof(res));

  ft_ping_init(&opts);
  if (ft_ping_parse(&opts, argc, argv) || ft_ping_exec(&res, opts))
    return (FT_EXFAIL);

  ft_ping_res(res, opts);

  return (FT_EXOK);
}
