/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap_exec_config.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/16 14:25:01 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void ft_nmap_init_config(t_nmap_ctx *ctx) {
  fprintf(
      stdout,
      "%s"
      " ------------------------------------------------------------------- \n"
      "| Init configuration                                                |\n"
      " ------------------------------------------------------------------- \n"
      "%s",
      PURPLE, DEFAULT);

  printf("Sniffing device: %s\n", ctx->sdev);
  printf("Source IP address: %s\n", ctx->saddr);
}

static void ft_nmap_exec_config_ip(char *sdev, char *saddr,
                                   const char ip[FT_NMAP_IP_MAX][256]) {
  int i = -1;

  printf("Sniffing device: %s\n", sdev);
  printf("Source IP address: %s\n", saddr);
  fprintf(stdout, "Target IP addresses: ");
  while (++i < FT_NMAP_IP_MAX && ft_strlen(ip[i]))
    fprintf(stdout, "%s ", ip[i]);
  fprintf(stdout, "\n");
}

static void ft_nmap_exec_config_ports(int nports, int *ports) {
  fprintf(stdout, "No of Ports to scan: %d (", nports);

  for (int i = 0; i < nports; i++) {
    fprintf(stdout, " %d", ports[i]);
  }

  fprintf(stdout, " )\n");
}

static void ft_nmap_exec_config_scans(int scans) {
  fprintf(stdout, "Scans to be perfomed: ");
  if (scans & FT_NMAP_SCAN_SYN) fprintf(stdout, "SYN ");
  if (scans & FT_NMAP_SCAN_NULL) fprintf(stdout, "NULL ");
  if (scans & FT_NMAP_SCAN_ACK) fprintf(stdout, "ACK ");
  if (scans & FT_NMAP_SCAN_FIN) fprintf(stdout, "FIN ");
  if (scans & FT_NMAP_SCAN_XMAS) fprintf(stdout, "XMAS ");
  if (scans & FT_NMAP_SCAN_UDP) fprintf(stdout, "UDP ");
  fprintf(stdout, "\n");
}

static void ft_nmap_exec_config_threads(int speedup) {
  fprintf(stdout, "No of threads: %d\n", speedup);
}

int ft_nmap_exec_config(t_nmap_ctx ctx, t_nmap_opts opts) {
  fprintf(stdout,
          "\n Scan configuration \n"
          " ------------------------------------------------ \n");

  ft_nmap_exec_config_ip(ctx.sdev, ctx.saddr, opts.ip);
  ft_nmap_exec_config_ports(opts.nports, opts.ports);
  ft_nmap_exec_config_scans(opts.scan);
  ft_nmap_exec_config_threads(opts.speedup);

  fprintf(stdout, " ------------------------------------------------ \n\n\n");
  // fprintf(stdout, "\n\n%s %15s %15s %15s\n\n", "Port", "Service Name",
  //         "Results", "Conclusion");

  return (FT_EXOK);
}
