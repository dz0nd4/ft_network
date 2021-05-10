/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/10 17:36:44 by user42           ###   ########lyon.fr   */
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
	return (EXIT_FAILURE);
}

int			ft_traceroute(int argc, const char *argv[])
{
	t_trace	ctx;

	ft_memset(&ctx, 0, sizeof(ctx));

	if (geteuid() != FT_TR_ROOT) {
		fprintf(stderr, "/!\\ You don't have root privileges /!\\\n");
		// return (EXIT_FAILURE);
	}

	if (argc < 2)
		return (ft_traceroute_usage((char *)argv[0]));

	if (ft_traceroute_parse(&ctx, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (ft_traceroute_execute(&ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
