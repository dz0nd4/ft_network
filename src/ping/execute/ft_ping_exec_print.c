/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/18 22:49:18 by user42           ###   ########lyon.fr   */
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
	time = ft_ping_execute_recv_print_time(&stats.time);
	printf("--- %s ping statistics ---\n", dst);
	printf("%d packets transmitted, ", stats.nbPcktSend);
	printf("%d packets received, ", stats.nbPcktReceive);
	printf("%d%% packets packet loss, ", percentPcktLoss);
	printf("time %0.fms\n", time);
	printf("rtt min/avg/nax/mdev = ");
	printf("%0.f/%0.f/%0.f/0.000\n", stats.minTime, stats.avgTime / stats.nbPcktReceive, stats.maxTime);
}

int		ft_ping_exec_print_infos(const char *dst, t_pg_sock	sock)
{
	t_sockaddr_in sockaddr_in;
	char ip[FT_ADDRSTRLEN];

	ft_memset(&sockaddr_in, 0, sizeof(t_sockaddr_in));
	ft_bzero(ip, FT_ADDRSTRLEN);
	ft_memcpy(&sockaddr_in, sock.addrinfo.ai_addr, sizeof(t_sockaddr_in));
	if (ft_sock_ntop((t_in_addr *)&sockaddr_in.sin_addr, ip) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	
	printf("PING %s (%s) 56(84) bytes of data.\n", dst, ip);
	return (EXIT_SUCCESS);
}

void     ft_ping_exec_print_pckt(int cc, char *addrbuf, char *packet, double time)
{
    t_ip *ip;
    t_icmp *icmp;
    int ttl;
    int seq;
	  char ipv4[FT_ADDRSTRLEN];
	  t_sockaddr_in sockaddr_in;
  
    ft_memcpy(&sockaddr_in, addrbuf, sizeof(t_sockaddr_in));

    if (ft_sock_ntop((t_in_addr *)&sockaddr_in.sin_addr, ipv4) == EXIT_FAILURE)
	  	return;
    
    ip = (t_ip *)&packet[0];
    icmp = (t_icmp *)&packet[sizeof(t_ip)];
    seq = icmp->icmp_hun.ih_idseq.icd_seq;
    ttl = ip->ip_ttl;
    printf("%d bytes from %s (%s): ", cc, ipv4, ipv4);
    printf("icmp_seq=%u ttl=%d, time=%0.2f ms\n", seq, ttl, time);
}