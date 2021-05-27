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

			// FD_ZERO(&fds);
  from = &ctx->from;
	ctx->opts.probes = -1;
	if (ft_traceroute_execute_init(ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	printf("traceroute to %s (%s), %d hops max, %d byte packets\n",
		ctx->to.name, ctx->to.ip, ctx->opts.hops_max, ctx->opts.packetlen);
	while (ctx->opts.hops < ctx->opts.hops_max) {

		printf("%2d ", ctx->opts.hops);
		while (ctx->opts.probes < ctx->opts.probes_max) {
			ft_traceroute_execute_send(ctx, &ctx->opts, &ctx->to);

				// FD_ZERO(&fds);

				// FD_SET(from->sfd, &fds);
					
				// if (select(from->sfd + 1, &fds, (fd_set *)0, (fd_set *)0, &from->wait)) {
					// if (FD_ISSET(from->sfd, &fds))
					// from->cc = 0;
					// if (select(from->sfd + 1, &fds, (fd_set *)0, (fd_set *)0, &from->wait))
					    from->cc = ft_sock_recv(from->sfd, from->buffer, BUF_SIZE, &from->saddrin);

						// from->cc == ft_traceroute_execute_recv(ctx, ctx->from.buffer, from);


							// break ;
				// }
				// printf("\nfromcc %d\n", from->cc);
				if (from->cc == 0) {
					printf(" *");
					if (ctx->opts.probes + 1 == ctx->opts.probes_max)
						putchar('\n');
					fflush(stdout);
				} else {
						ft_traceroute_execute_recv_print(ctx);
				}
			ctx->opts.probes += 1;	
		}
		ctx->opts.probes = 0;
		ctx->opts.hops += 1;
	}

	return (EXIT_SUCCESS);
}
