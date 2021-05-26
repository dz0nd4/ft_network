/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_finish.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 17:18:10 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int  ft_ping_exec_finish(t_pg_opts opts, t_pg_sock *sock, t_pg_stats *stats)
{
	double nbPcktLoss;
	double percentPcktLoss;
	double time;

	ft_sock_gettime(&stats->time.stop);
	nbPcktLoss = stats->nbPcktSend - stats->nbPcktReceive;
	percentPcktLoss = stats->nbPcktSend ? nbPcktLoss / stats->nbPcktSend * 100 : 0;
	time = ft_sock_timediff(&stats->time.stop, &stats->time.start);

	printf("\n--- %s ping statistics ---\n", opts.dest);
	printf("%d packets transmitted, ", stats->nbPcktSend);
	printf("%d packets received, ", stats->nbPcktReceive);
	printf("%0.f%% packets packet loss, ", percentPcktLoss);
	printf("time %0.fms\n", time);

	if (stats->nbPcktSend > 0 && stats->maxTime > 0 && opts.packetsize >= FT_TIMEVAL_LEN) {
		printf("rtt min/avg/max = ");
		printf("%0.3f/%0.3f/%0.3f", stats->minTime, stats->avgTime / stats->nbPcktReceive, stats->maxTime);
	}

	printf("\n");

	free(sock->pckt_send.msg);
	free(sock->pckt_recv.msg);
	close(sock->fd);

	return(EXIT_SUCCESS);
}