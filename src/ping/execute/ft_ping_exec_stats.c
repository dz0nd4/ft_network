/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_stats.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 13:54:52 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int  ft_ping_exec_stats(t_pg_stats stats)
{
	int nbPcktLoss;
	int percentPcktLoss;
	double time;

	nbPcktLoss = stats.nbPcktSend - stats.nbPcktReceive;
	percentPcktLoss = (nbPcktLoss / stats.nbPcktSend) * 100;
	// time = ft_ping_execute_recv_print_time(&stats.time);
	time = ft_sock_getelapsedtime(&stats.time.start);
	printf("--- %s ping statistics ---\n", g_pg.sock.host);
	printf("%d packets transmitted, ", stats.nbPcktSend);
	printf("%d packets received, ", stats.nbPcktReceive);
	printf("%d%% packets packet loss, ", percentPcktLoss);
	printf("time %0.fms\n", time);

	if (stats.nbPcktReceive > 0) {
		printf("rtt min/avg/max = ");
		printf("%0.f/%0.f/%0.f", stats.minTime, stats.avgTime / stats.nbPcktReceive, stats.maxTime);
	}

	printf("\n");
}

