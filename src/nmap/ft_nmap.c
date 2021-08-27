/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/26 17:12:00 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

int ft_nmap_usage() {
  fprintf(
      stderr,
      "Usage: nmap [OPTIONS]\n"
      "Options:\n"
      "  --help		  Show help\n"
      "  --ports    Ports to scan (eg: 1-10 or 1,2,3 or 1,5-15). Default is "
      "1-1024\n"
      "  --ip       Ip addresses to scan in dot format\n"
      "  --file     File name containing IP addresses to scan\n"
      "  --speedup  Number of parallel threads to use. Max is 250. Default is "
      "0\n"
      "  --scan     Type of scan. Must be one of SYN/NULL/FIN/XMAS/ACK/UDP. "
      "Default is all\n");
  return (FT_EXFAIL);
}

int ft_nmap_init(t_nmap_ctx *ctx, t_nmap_opts *opts) {
  ft_memset(ctx, 0, sizeof(*ctx));
  ft_memset(opts, 0, sizeof(*opts));

  if (ft_pcap_lookupdev(
          &ctx->sdev))  // ft_pcap_lookupnet(ctx->sdev, &ctx->net, &ctx->mask))
    return (FT_EXFAIL);

  if (ft_getifaddr((const char *)ctx->sdev, &ctx->saddr)) {
    return (FT_EXFAIL);
  }

  opts->nports = 1024;
  opts->scan = FT_NMAP_SCAN_SYN | FT_NMAP_SCAN_NULL | FT_NMAP_SCAN_ACK |
               FT_NMAP_SCAN_FIN | FT_NMAP_SCAN_XMAS | FT_NMAP_SCAN_UDP;
  opts->speedup = 1;
  // ft_nmap_init_config(ctx);

  return (FT_EXOK);
}

// int ft_nmap_execute_init(t_nmap_ctx ctx, t_nmap_opts opts) {}

int ft_nmap(int argc, const char *argv[]) {
  t_nmap_ctx ctx;
  t_nmap_opts opts;

  if (argc < 2) {
    return (ft_nmap_usage());
  }

  if (ft_nmap_init(&ctx, &opts) == FT_EXFAIL) {
    fprintf(stderr, "Failing initialize nmap. Exiting...\n");
  }

  if (ft_nmap_parse(&opts, argc, argv) == FT_EXFAIL) {
    return (FT_EXFAIL);
  }

  ft_nmap_config_global(ctx, opts);

  ft_nmap_exec2(&ctx, &opts);

  return (FT_EXOK);
}
