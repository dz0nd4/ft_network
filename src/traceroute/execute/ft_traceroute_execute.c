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

static int 	ft_traceroute_execute_init(t_trace *ctx)
{
	if (ft_traceroute_execute_send_init(&ctx->to) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (ft_traceroute_execute_pack_init(ctx, &ctx->to) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (ft_traceroute_execute_recv_init(&ctx->from) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	
	return (EXIT_SUCCESS);
}

int 		ft_traceroute_execute(t_trace *ctx)
{
	int cc;
  char buffer[BUF_SIZE];
  t_tr_from *from;
  fd_set    fds;

			FD_ZERO(&fds);
  from = &ctx->from;
	ctx->opts.probes = -1;
	if (ft_traceroute_execute_init(ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	printf("traceroute to %s (%s), %d hops max, %d byte packets\n",
		ctx->to.name, ctx->to.ip, ctx->opts.hops_max, ctx->opts.packetlen);
	while (ft_traceroute_execute_send(ctx, &ctx->opts, &ctx->to)) {
			FD_ZERO(&fds);
			FD_SET(from->sfd, &fds);
			from->cc = 0;
			if (select(from->sfd + 1, &fds, (fd_set *)0, (fd_set *)0, &from->wait) > 0) {
				if (ft_traceroute_execute_recv(ctx, ctx->from.buffer, from) == EXIT_SUCCESS)
					break ;
			}
			if (from->cc == 0) {
				printf(" *");
				fflush(stdout);
			}
	}

	return (EXIT_SUCCESS);
}
