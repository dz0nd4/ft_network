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

#include "ft_traceroute.h"

static int ft_isopt(char *opt) {
  if (*opt && *opt == '-' && ft_strlen(opt) > 1) return (FT_TRUE);
  return (FT_FALSE);
}

static int ft_trace_parse_init(t_tr_opts *opts, t_arg *arg) {
  arg->i = 1;

  opts->argi = 1;
  opts->hops = FT_HOPS_FIRST_DEFAULT;
  opts->hops_max = FT_HOPS_MAX_DEFAULT;
  opts->probes_max = FT_PROBES_DEFAULT;
  opts->port = FT_PORT_DEFAULT;
  opts->packetlen = FT_IPHDR_LEN + 40;

  if (geteuid() != FT_TR_ROOT) {
    fprintf(stderr, "/!\\ You don't have root privileges /!\\\n");
    // return (EXIT_FAILURE);
  }

  if (arg->c < 2) return (ft_traceroute_usage());

  return (FT_EXOK);
}

static int ft_trace_parse_opt(t_tr_opts *opts, t_arg *arg) {
  static t_tr_opt_d ft_tr_opt[FT_TR_OPT_MAX] = {
      {FT_TR_OPT_F, "f", ft_tr_opt_f},
      {FT_TR_OPT_M, "m", ft_tr_opt_m},
      {FT_TR_OPT_Q, "q", ft_tr_opt_q},
      {FT_TR_OPT_H, "h", ft_tr_opt_h},
  };
  int opt_key;
  const char *opt_name;

  opt_key = -1;
  opt_name = arg->v[arg->i] + 1;
  while (++opt_key < FT_TR_OPT_MAX)
    if (ft_strequ(ft_tr_opt[opt_key].opt_name, opt_name))
      return (ft_tr_opt[opt_key].opt_dist(opts, arg));
  fprintf(stderr, "Bad option `%s` (argc %d)\n", opt_name, arg->i);
  return (FT_EXFAIL);
}

int ft_trace_parse(t_tr_opts *opts, int argc, const char *argv[]) {
  t_arg arg;

  arg.i = 0;
  arg.c = argc;
  arg.v = argv;

  if (ft_trace_parse_init(opts, &arg) == FT_EXFAIL) return (FT_EXFAIL);

  while (arg.i < arg.c) {
    if (ft_isopt(arg.v[arg.i])) {
      if (ft_trace_parse_opt(opts, &arg) == FT_EXFAIL) return (FT_EXFAIL);
    } else {
      (opts->host == NULL) ? ft_tr_arg_host(opts, &arg)
                           : ft_tr_arg_packetlen(opts, &arg);
      arg.i += 1;
    }
  }

  if (opts->host == NULL) {
    fprintf(stderr, "Specify \"host\" missing argument.\n");
    return (FT_EXFAIL);
  }

  if (opts->hops > opts->hops_max) {
    fprintf(stderr, "first hop out of range\n");
    return (FT_EXFAIL);
  }

  return (FT_EXOK);
}
