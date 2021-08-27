/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 12:33:29 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static int ft_isopt(char *opt) {
  if (ft_strlen(opt) > 2 && ft_strncmp(opt, "--", 2) == 0) return (FT_TRUE);
  return (FT_FALSE);
}

static int ft_nmap_parse_opt(t_nmap_opts *opts, t_arg *arg) {
  const t_nmap_opts_d ft_tr_opt[FT_NMAP_OPT_MAX] = {
      {FT_NMAP_OPT_PORTS, "ports", ft_nmap_opt_ports},
      {FT_NMAP_OPT_IP, "ip", ft_nmap_opt_ip},
      {FT_NMAP_OPT_FILE, "file", ft_nmap_opt_file},
      {FT_NMAP_OPT_SPEEDUP, "speedup", ft_nmap_opt_speedup},
      {FT_NMAP_OPT_SCAN, "scan", ft_nmap_opt_scan},
      {FT_NMAP_OPT_HELP, "h", ft_nmap_opt_help},
  };
  int opt_key;
  const char *opt_name;

  opt_key = -1;
  opt_name = arg->v[arg->i] + 2;
  while (++opt_key < FT_NMAP_OPT_MAX)
    if (ft_strequ(ft_tr_opt[opt_key].opt_name, opt_name))
      return (ft_tr_opt[opt_key].opt_dist(opts, arg));
  fprintf(stderr, "Bad option `%s` (argc %d)\n", opt_name, arg->i);
  return (FT_EXFAIL);
}

int ft_nmap_parse(t_nmap_opts *opts, int argc, const char *argv[]) {
  t_arg arg;

  arg.i = 1;
  arg.c = argc;
  arg.v = argv;

  while (arg.i < arg.c) {
    if (!ft_isopt(arg.v[arg.i])) {
      fprintf(stderr, "Invalid argument `%s` (argc %d)\n", arg.v[arg.i], arg.i);
      return (FT_EXFAIL);
    }
    if (ft_nmap_parse_opt(opts, &arg) == FT_EXFAIL) return (FT_EXFAIL);
  }

  if (opts->ip == NULL && opts->file == NULL) {
    fprintf(stderr, "--ip or --file options missing\n");
    return (FT_EXFAIL);
  }

  return (FT_EXOK);
}
