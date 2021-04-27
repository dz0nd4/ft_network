/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_execute.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/27 17:53:22 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static int 	ft_traceroute_execute_init(t_trace *ctx)
{
	if (ft_traceroute_socket_send_init(ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (ft_traceroute_socket_receive_init(ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (ft_traceroute_packet_init(ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}

int 		ft_traceroute_execute(t_trace *ctx)
{
	int cc;
  char buffer[BUF_SIZE];

	ft_traceroute_execute_init(ctx);
	ft_traceroute_display_infos_host(ctx);
	while (ctx->opts.hops <= ctx->opts.hops_max) {
		ctx->opts.probes = 0;
		while (ctx->opts.probes < ctx->opts.probes_max) {
			ft_traceroute_socket_send(ctx);
			cc = ft_traceroute_socket_receive(ctx, buffer);
			if (ft_traceroute_packet_check(ctx, buffer) == EXIT_SUCCESS)
				ft_traceroute_print(ctx, cc);

			ctx->opts.probes++;
		}
		
		printf("\n");
		if (ctx->from.code == ICMP_UNREACH)
			break;
		// if (ft_strequal(ctx->to.ip, inet_ntoa(ctx->from.saddrin.sin_addr)))
		// 	break;

		ctx->opts.hops++;
	}

	return (EXIT_SUCCESS);
}
