/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 18:41:23 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int g_ping = FT_PG_RUN;

void 	ft_ping_sigint()
{
	g_ping = FT_PG_STOP;
}

void 	ft_ping_sigarlm()
{
	if (g_ping != FT_PG_STOP) {
		g_ping = FT_PG_SEND;
		alarm(FT_PING_DEFAULT_DELAY);
	}
}

int  ft_ping_usage()
{
	fprintf(stderr, "Usage: ping [-ahv] destination\n");
	return(EXIT_FAILURE);
}

int			ft_ping(int argc, const char *argv[])
{
	t_pg_opts 	opts;
	t_pg_sock 	sock;
	t_pg_stats 	stats;

	ft_memset(&opts, 0, sizeof(opts));
	ft_memset(&sock, 0, sizeof(sock));
	ft_memset(&stats, 0, sizeof(stats));
	
	if (ft_ping_parse(&opts, argc, argv) == FT_EXFAIL)
		return (FT_EXFAIL);

	if (ft_ping_exec_init(opts, &sock, &stats) == FT_EXFAIL)
		return (FT_EXFAIL);

	signal(SIGINT, ft_ping_sigint);
	signal(SIGALRM, ft_ping_sigarlm);
	
	alarm(FT_PING_DEFAULT_DELAY);

	while (g_ping >= FT_PG_RUN) {
		if (g_ping == FT_PG_SEND) {
			if (ft_ping_exec_send(&sock, opts, &stats) == FT_EXFAIL)
				break;
			if (ft_ping_exec_receive(&sock, opts, &stats) == FT_EXOK)
				ft_ping_exec_pckt(&sock, opts, &stats);
			if (g_ping != FT_PG_STOP)
				g_ping = FT_PG_RUN;
		}
	}

	ft_ping_exec_finish(opts, &sock, &stats);

	return (FT_EXOK);
}
