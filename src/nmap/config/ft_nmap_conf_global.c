/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap_conf_global.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/22 19:41:49 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

// static void ft_nmap_exec_config_ports(int nports, int *ports) {
//   fprintf(stdout, "No of Ports to scan: %d (", nports);

//   for (int i = 0; i < nports; i++) {
//     fprintf(stdout, " %d", ports[i]);
//   }

//   fprintf(stdout, " )\n");
// }

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

int ft_nmap_config_global(t_nmap_ctx ctx, t_nmap_opts opts) {
  fprintf(stdout,
          "\n Gobal Configuration \n"
          " ------------------------------------------------ \n");

  // ft_nmap_exec_config_ip(ctx.sdev, ctx.saddr, opts.ip);
  printf("Sniffing device: %s\n", ctx.sdev);
  printf("Source IP address: %s\n\n", ctx.saddr);

  fprintf(stdout, "No of IPs to scan: %d\n", opts.nip);
  fprintf(stdout, "No of Ports to scan: %d\n", opts.nports);
  // ft_nmap_exec_config_ports(opts.nports, opts.ports);
  ft_nmap_exec_config_scans(opts.scan);
  fprintf(stdout, "No of threads: %d\n", opts.speedup);

  // ft_nmap_exec_config_threads(opts.speedup);

  fprintf(stdout, " ------------------------------------------------ \n");
  // fprintf(stdout, "\n\n%s %15s %15s %15s\n\n", "Port", "Service Name",
  //         "Results", "Conclusion");

  return (FT_EXOK);
}
