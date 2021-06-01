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

int 	ft_traceroute_exec_init(t_trace *ctx, t_tr_to *to)
{
	if (ft_traceroute_exec_send_init(ctx, to) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (ft_traceroute_exec_pack_init(ctx, to) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	// if (ft_traceroute_execute_recv_init(&ctx->from) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);

	
	return (EXIT_SUCCESS);
}

int 		ft_traceroute_exec(t_trace *ctx, t_tr_opts *opts)
{
	t_tr_to to;
	t_tr_from from;

	if (ft_traceroute_exec_init(ctx, &to) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// ft_traceroute_execute_recv_init(&from);

	printf("traceroute to %s (%s), %d hops max, %d byte packets",
		to.name, to.ip, opts->hops_max, opts->packetlen);

	while (opts->hops < opts->hops_max) {
		printf("\n%2d ", opts->hops);

		while (opts->probes < opts->probes_max) {
			ft_traceroute_exec_send(opts, &to);
	
			if (ft_traceroute_exec_recv(opts, &to, &from) == FT_EXOK)
				ft_traceroute_exec_recv_print(opts, &from, to);
			else
				printf(" *");

			close(from.sfd);
			fflush(stdout);
			opts->probes += 1;	
		}

		opts->probes = 0;
		opts->hops += 1;
	}

	return (EXIT_SUCCESS);
}
