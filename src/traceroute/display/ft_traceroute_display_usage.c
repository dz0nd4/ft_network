/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_usage.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/20 15:40:21 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

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

