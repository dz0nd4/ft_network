/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 23:42:41 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void 	ft_ping_sigint()
{
	g_ping = FT_PG_STOP;
}

void 	ft_ping_sigarlm()
{
	g_ping = FT_PG_SEND;
	alarm(FT_PING_DEFAULT_DELAY);
}

int  ft_ping_usage()
{
	fprintf(stderr, "Usage: ping [-ahv] destination\n");
	return(EXIT_FAILURE);
}

int			ft_ping(int argc, const char *argv[])
{
	t_pg_args 	args;
	t_pg_opts 	opts;
	t_pg_sock 	sock;
	t_pg_stats 	stats;

	ft_ping_opts_init(argc, argv, &args, &opts);
	while (argv[args.argi] && *argv[args.argi] == '-') {
		if (ft_ping_opts_parse(&opts, &args) == FT_EXFAIL)
			return (FT_EXFAIL);
	}

	if (argv[args.argi] == NULL)
		return (ft_ping_usage());

	if (ft_ping_exec_init(argv[args.argi], &sock, opts, &stats) == FT_EXFAIL)
		return (FT_EXFAIL);

	signal(SIGINT, ft_ping_sigint);
	signal(SIGALRM, ft_ping_sigarlm);
	
	alarm(FT_PING_DEFAULT_DELAY);
	while (g_ping) {
		if (g_ping == FT_PG_SEND) {
			if (ft_ping_exec_send(&sock, opts, &stats) == FT_EXOK)
				ft_ping_exec_receive(&sock, opts, &stats);
			g_ping = FT_PG_RUN;
		}
	}

	ft_ping_exec_finish(argv[args.argi], &sock, &stats);

	return (FT_EXOK);
}
