/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/27 00:48:40 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int			ft_traceroute_usage(char *prgm)
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "  %s ", prgm);
	fprintf(stderr, "[ -f firt_ttl ] [ -m max_ttl ] [ -q nqueries ] host\n");
	
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "  -f first_ttl		Start from the first_ttl hop (instead from 1)\n");
	fprintf(stderr, "  -m max_ttl		Set the max number of hops (max TTL to be reached). Default is 30\n");
	fprintf(stderr, "  -q nqueries		Set the number of probes per each hop. Default is 3\n\n");

	fprintf(stderr, "Arguments:\n");
	fprintf(stderr, "+     host	The host to traceroute to\n");
	return (FT_EXFAIL);
}

int			ft_traceroute(int argc, const char *argv[])
{
	t_trace	ctx;
	// t_tr_to to;
	// t_tr_from from;
	t_tr_opts *opts = &ctx.opts;
	t_tr_sock	to;
	t_tr_sock	from;

	ft_memset(&ctx, 0, sizeof(ctx));

	if (ft_traceroute_parse(&ctx, argc, argv) == FT_EXFAIL)
		return (FT_EXFAIL);

	if (ft_traceroute_exec_init_to(&ctx, &to) == FT_EXFAIL)
		return (FT_EXFAIL);

	// if (ft_traceroute_exec_init_from(&ctx.opts, &from) == FT_EXFAIL)
	// 	return (FT_EXFAIL);
	// if (ft_traceroute_exec_init_from(opts, &from) == FT_EXFAIL)
	// 	return (FT_EXFAIL);
	
	// printf("traceroute to %s (%s), %d hops max, %d byte packets",
	// 	opts->host, inet_ntoa(to.saddrin.sin_addr), opts->hops_max, opts->packetlen);

	// while (opts->hops < opts->hops_max) {
	// 	printf("\n%2d ", opts->hops);

		ft_traceroute_exec(&ctx.opts, &to, &from);
	ft_traceroute_exec_finish_to(&ctx, &to);
	// 	opts->probes = 0;
	// 	opts->hops += 1;
	// }

	return (FT_EXOK);
}
