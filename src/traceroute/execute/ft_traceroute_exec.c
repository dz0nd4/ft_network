/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_execute.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/27 01:01:15 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int 		ft_traceroute_exec(t_tr_opts *opts, t_tr_sock *to, t_tr_sock *prom)
{
	t_tr_sock from;

	printf("traceroute to %s (%s), %d hops max, %d byte packets",
		opts->host, inet_ntoa(to->saddrin.sin_addr), opts->hops_max, opts->packetlen);

  // ft_traceroute_execute_recv_init(&from);
	while (opts->hops < opts->hops_max) {
		printf("\n%2d ", opts->hops);

		if (ft_traceroute_exec_init_from(opts, &from) == FT_EXFAIL)
			return (FT_EXFAIL);

		while (opts->probes < opts->probes_max) {
			// ft_traceroute_exec_send(opts, to);
			ft_traceroute_exec_send(opts, to);

			if (ft_traceroute_exec_recv(opts, to, &from) == FT_EXOK)
				ft_traceroute_exec_pckt(opts, to, &from);
			else
				printf(" *");

			fflush(stdout);
			opts->probes += 1;
		}

		ft_traceroute_exec_finish_from(opts, &from);

		opts->probes = 0;
		opts->hops += 1;
	}

	return (EXIT_SUCCESS);
}
