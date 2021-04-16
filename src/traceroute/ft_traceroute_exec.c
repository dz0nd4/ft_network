/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/06 13:17:47 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int 		ft_traceroute_exec(t_trace *ctx)
{
	int hops;
	int probes;
	int cc;

	hops = 1;
	while (ctx->args.hops <= ctx->args.hops_max) {
		ctx->args.probes = 0;
		while (ctx->args.probes < ctx->args.probes_max) {
			ft_traceroute_send(ctx);
			cc = ft_traceroute_receive(ctx);
			ft_traceroute_print(ctx, cc);

			ctx->args.probes++;
		}
		
		printf("\n");

		if (ft_strequal(ctx->host.ip, inet_ntoa(ctx->from.sin_addr)))
			break;

		ctx->args.hops++;
	}

	return (EXIT_SUCCESS);
}
