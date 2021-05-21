/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 14:43:51 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int  ft_ping_exec_print_stats(const char *dst, t_pg_stats stats)
{
	int nbPcktLoss;
	int percentPcktLoss;
	double time;

	nbPcktLoss = stats.nbPcktSend - stats.nbPcktReceive;
	percentPcktLoss = nbPcktLoss / stats.nbPcktSend;
	// time = ft_ping_execute_recv_print_time(&stats.time);
	printf("--- %s ping statistics ---\n", dst);
	printf("%d packets transmitted, ", stats.nbPcktSend);
	printf("%d packets received, ", stats.nbPcktReceive);
	printf("%d%% packets packet loss, ", percentPcktLoss);
	printf("time %0.fms\n", time);
	printf("rtt min/avg/nax/mdev = ");
	printf("%0.f/%0.f/%0.f/0.000\n", stats.minTime, stats.avgTime / stats.nbPcktReceive, stats.maxTime);
}

int  ft_ping_exec_print_stats2(t_pg_stats stats)
{
	int nbPcktLoss;
	int percentPcktLoss;
	double time;

	nbPcktLoss = stats.nbPcktSend - stats.nbPcktReceive;
	percentPcktLoss = nbPcktLoss / stats.nbPcktSend;
	// time = ft_ping_execute_recv_print_time(&stats.time);
	printf("--- %s ping statistics ---\n", "");
	printf("%d packets transmitted, ", stats.nbPcktSend);
	printf("%d packets received, ", stats.nbPcktReceive);
	printf("%d%% packets packet loss, ", percentPcktLoss);
	printf("time %0.fms\n", time);
	printf("rtt min/avg/nax/mdev = ");
	printf("%0.f/%0.f/%0.f/0.000\n", stats.minTime, stats.avgTime / stats.nbPcktReceive, stats.maxTime);
}


int		ft_ping_exec_print_infos(const char *dst, t_pg_sock	sock, t_pg_opts opts)
{
	t_sockaddr_in sockaddr_in;
	char ip[FT_ADDRSTRLEN];

	ft_memset(&sockaddr_in, 0, sizeof(t_sockaddr_in));
	ft_bzero(ip, FT_ADDRSTRLEN);
	// ft_memcpy(&sockaddr_in, sock.addrinfo.ai_addr, sizeof(t_sockaddr_in));
	// if (ft_sock_ntop((t_in_addr *)&sockaddr_in.sin_addr, ip) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);

	printf("PING %s (%s) %d(%d) bytes of data.\n", dst, ip, opts.packetsize, opts.packetsize + FT_PING_ICMPHDR);
	return (EXIT_SUCCESS);
}

int     ft_ping_exec_print_pckt(int cc, char *addr, int seq, int ttl, double time)
{
	  char ipv4[FT_ADDRSTRLEN];
		char hostname[FT_NI_MAXHOST];
	  t_sockaddr_in sockaddr_in;
  
    ft_memcpy(&sockaddr_in, addr, sizeof(t_sockaddr_in));

    if (ft_sock_ntop((t_in_addr *)&sockaddr_in.sin_addr, ipv4) == EXIT_FAILURE)
	  	return (FT_EXFAIL);

		ft_socket_getnameinfo(&sockaddr_in, hostname);

    printf("%d bytes from %s (%s): ", cc, hostname, ipv4);
    printf("icmp_seq=%u ttl=%d, time=%0.2f ms\n", seq, ttl, time);
		return (FT_EXOK);
}


int     ft_pg_exec_print_pckt(char *addr, int seq, int icmp_type)
{
	  t_sockaddr_in sockaddr_in;
	  char ipv4[FT_ADDRSTRLEN];
		char hostname[FT_NI_MAXHOST];

    ft_memcpy(&sockaddr_in, addr, sizeof(t_sockaddr_in));

    if (ft_sock_ntop((t_in_addr *)&sockaddr_in.sin_addr, ipv4) == EXIT_FAILURE)
	  	return (FT_EXFAIL);

		ft_socket_getnameinfo(&sockaddr_in, hostname);

    printf("From %s (%s): ", hostname, ipv4);
    printf("icmp_seq=%u %s\n", seq, ft_sock_get_icmp_type(icmp_type));
		return (FT_EXOK);
}
