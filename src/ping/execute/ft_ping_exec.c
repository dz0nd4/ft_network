/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 23:34:45 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int g_ping_run = 1;
int g_ping = FT_PG_RUN;

#define RECV_TIMEOUT 1

/*
 * ft_pg_exec_init_pckt
 *
 * Description:
 *   Dynamic allocate packets for sending and receiving data 
 * Returns:
 *   ft_ping_usage function
*/
static int  ft_pg_exec_init_pckt(t_pg_sock *sock, t_pg_opts opts)
{
	t_icmphdr	*hdr;
	t_timeval *tv;
	int i;

	sock->send_pckt_len = FT_ICMPHDR_LEN + opts.packetsize;
	sock->send_pckt = (unsigned char *)ft_memalloc(sock->send_pckt_len);
	if (sock->send_pckt == NULL)
		return (FT_EXFAIL);
	hdr = (t_icmphdr *)&sock->send_pckt[0];
	tv = (t_timeval *)&sock->send_pckt[FT_ICMPHDR_LEN];	
	i = FT_ICMPHDR_LEN;

	hdr->type = ICMP_ECHO;
	hdr->un.echo.id = sock->id;
	hdr->un.echo.sequence = 0;
	hdr->checksum = 0;

	while (i < (sock->send_pckt_len - 1))
		sock->send_pckt[i++] = i + '0';
	sock->send_pckt[i] = 0;

	sock->recv_pckt_len = FT_PING_ICMPHDR + opts.packetsize;
	sock->recv_pckt = (unsigned char *)ft_memalloc(sock->recv_pckt_len);
	if (sock->recv_pckt == NULL) {
		free(sock->send_pckt);
		return (FT_EXFAIL);
	}
	return (FT_EXOK);
}

/*
 * ft_pg_exec_init_sock
 *
 * Description:
 *   Init socket with custom TTL from opts. Default timeout to 1s 
 * Returns:
 * 
*/
static int  ft_pg_exec_init_sock(const char *dst, t_pg_sock *sock, t_pg_opts opts)
{	
	t_addrinfo 	addrinfo;
	t_timeval		tv;

	ft_memset(&addrinfo, 0, sizeof(addrinfo));
	ft_memset(&tv, 0, sizeof(tv));
	tv.tv_sec = 1;

	if (ft_sock_getaddrinfo(dst, &addrinfo) == EXIT_FAILURE) {
		fprintf(stderr, "%s: Échec temporaire dans la résolution du nom\n", dst);
		return (FT_EXFAIL);
	}

	sock->id = getpid() & 0xFFFF;
	sock->fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	ft_memcpy(&sock->addrin, addrinfo.ai_addr, sizeof(t_sockaddr_in));

  if (sock->fd == INVALID_SOCKET) {
		if (opts.verbose)
			fprintf(stderr, "ping: socket: Permission denied, attempting raw socket...\n");

		if((sock->fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == INVALID_SOCKET)
			return (FT_EXFAIL);
	}

  if (setsockopt(sock->fd, IPPROTO_IP, IP_TTL, &opts.ttl, sizeof(opts.ttl)) != 0)
		if (opts.verbose == 1)
			fprintf(stderr, "Set TTL option failed.\n");

  if (setsockopt(sock->fd, IPPROTO_IP, SO_RCVTIMEO, (const char*)&tv, sizeof(tv)) != 0)
		if (opts.verbose == 1)
			fprintf(stderr, "Set RECVTIMEOUT option failed.\n");

	return (EXIT_SUCCESS);
}

int  ft_ping_exec_init(const char *dst, t_pg_sock *sock, t_pg_opts opts, t_pg_stats *stats)
{	
	char ip[FT_ADDRSTRLEN];

	if (!(getuid() == 0))
		if (opts.verbose)
			fprintf(stderr, "No privileges \n");
	
	if (ft_pg_exec_init_sock(dst, sock, opts) == FT_EXFAIL)
		return (FT_EXFAIL);

	if (ft_pg_exec_init_pckt(sock, opts) == FT_EXFAIL)
		return (FT_EXFAIL);

	if (ft_sock_ntop((t_in_addr *)&sock->addrin.sin_addr, ip) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	printf("PING %s (%s) %d(%d) bytes of data.\n",
		dst, ip, opts.packetsize, opts.packetsize + FT_PING_ICMPHDR);

	ft_sock_gettime(&stats->time.start);

	return (EXIT_SUCCESS);
}


int  ft_ping_exec_finish(const char *dst, t_pg_sock *sock, t_pg_stats *stats)
{
	int nbPcktLoss;
	int percentPcktLoss;
	double time;

	ft_sock_gettime(&stats->time.stop);
	nbPcktLoss = stats->nbPcktSend - stats->nbPcktReceive;
	percentPcktLoss = stats->nbPcktSend ? nbPcktLoss / stats->nbPcktSend : 0;
	time = ft_sock_timediff(&stats->time.stop, &stats->time.start);

	printf("\n--- %s ping statistics ---\n", dst);
	printf("%d packets transmitted, ", stats->nbPcktSend);
	printf("%d packets received, ", stats->nbPcktReceive);
	printf("%d%% packets packet loss, ", percentPcktLoss);
	printf("time %0.fms\n", time);

	if (stats->nbPcktSend > 0) {
		printf("rtt min/avg/nax/mdev = ");
		printf("%0.f/%0.f/%0.f/0.000\n", stats->minTime, stats->avgTime / stats->nbPcktReceive, stats->maxTime);
	}

	free(sock->send_pckt);
	free(sock->recv_pckt);
	close(sock->fd);

	return(EXIT_SUCCESS);
}