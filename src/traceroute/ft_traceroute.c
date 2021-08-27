/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/07/27 16:51:07 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int ft_traceroute_usage() {
  fprintf(
      stderr,
      "Usage:\n"
      "traceroute [ -f first_ttl ] [ -m max_ttl ] [ -q nqueries ] host\n"
      "Options:\n"
      "  -f first_ttl		Start from the first_ttl hop (instead from 1)\n"
      "  -m max_ttl		Set the max number of hops (max TTL to be "
      "reached). Default is 30\n"
      "  -q nqueries		Set the number of probes per each hop. Default "
      "is 3\n\n"
      "Arguments:\n"
      "  host	                The host to traceroute to\n"
      "  packetlen             The full packet length (default is the length "
      "of an IP header plus 40). Can be ignored or increased to a minimal "
      "allowed value\n\n");
  return (FT_EXFAIL);
}

int ft_traceroute(int argc, const char *argv[]) {
  t_tr_opts opts;
  t_tr_sock to;
  t_tr_sock from;

  ft_memset(&opts, 0, sizeof(opts));

  if (ft_trace_parse(&opts, argc, argv) || ft_trace_exec_init_to(&opts, &to))
    return (FT_EXFAIL);

  printf("traceroute to %s (%s), %d hops max, %d byte packets", opts.host,
         inet_ntoa(to.saddrin.sin_addr), opts.hops_max, opts.packetlen);

  while (opts.hops <= opts.hops_max) {
    printf("\n%2d ", opts.hops);
    if (ft_trace_exec_init_from(&opts, &from) == FT_EXFAIL) return (FT_EXFAIL);

    while (opts.probes < opts.probes_max) {
      ft_trace_exec_send(&opts, &to);

      if (ft_trace_exec_recv(&opts, &to, &from) == FT_EXOK) return (FT_EXOK);

      opts.probes += 1;
    }
    ft_trace_exec_finish_from(&opts, &from);

    opts.probes = 0;
    opts.hops += 1;
  }

  ft_trace_exec_finish_to(&to);

  return (FT_EXOK);
}
