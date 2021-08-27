/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace_execute.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/27 01:01:15 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int ft_trace_execute(t_tr_opts *opts, t_tr_sock *to, t_tr_sock *prom) {
  t_tr_sock from;

  if (ft_trace_exec_init_to(opts, to) == FT_EXFAIL) return (FT_EXFAIL);

  printf("traceroute to %s (%s), %d hops max, %d byte packets", opts->host,
         inet_ntoa(to->saddrin.sin_addr), opts->hops_max, opts->packetlen);

  // ft_trace_execute_recv_init(&from);
  while (opts->hops < opts->hops_max) {
    printf("\n%2d ", opts->hops);

    if (ft_trace_exec_init_from(opts, &from) == FT_EXFAIL) return (FT_EXFAIL);
    while (opts->probes < opts->probes_max) {
      ft_trace_exec_send(opts, to);

      if (ft_trace_exec_recv(opts, to, &from) == FT_EXFAIL)
        printf(" *");
      else {
        if (ft_trace_exec_pckt(opts, to, &from) == FT_EXOK) break;
      }

      fflush(stdout);
      opts->probes += 1;
    }
    if (ft_trace_exec_finish_from(opts, &from) == FT_EXOK) break;

    opts->probes = 0;
    opts->hops += 1;
  }

  ft_trace_exec_finish_to(to);

  return (EXIT_SUCCESS);
}
