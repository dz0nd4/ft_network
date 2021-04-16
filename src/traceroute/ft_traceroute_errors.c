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

int			ft_traceroute_help(char *prgm)
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

int			ft_traceroute_perm()
{
	printf("/!\\ You don't have root privileges /!\\\n");
	return (EXIT_FAILURE);
	// return (ft_traceroute_help());
}

void ft_exit(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void ft_traceroute_exit(char *s)
{
	fprintf(stderr, "%s\n", s);
	exit(EXIT_FAILURE);
}

int 	ft_tr_error_bad_opt(t_trace *ctx, char *opt)
{
	fprintf(stderr, "Bad option `%s` (argc %d)\n", opt, ctx->argi);
	return (EXIT_FAILURE);
}

int 	ft_tr_error_arg(t_trace *ctx, char *opt, char *arg)
{
	fprintf(stderr, "Option `%s` (argc %d) requires an argument: `%s %s`",
						opt, ctx->argi, opt, arg);
	return (EXIT_FAILURE);
}

int 	ft_tr_error_arg_handle(t_trace *ctx, char *opt, char *arg)
{
	fprintf(stderr, "Cannot handle `%s' option with arg `%s' (argc %d)",
						opt, arg, ctx->argi);
	return (EXIT_FAILURE);
}