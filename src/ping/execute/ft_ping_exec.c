/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 15:42:45 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

/*
 * ft_pg_exec_init_pckt
 *
 * Description:
 *   Dynamic allocate packets for sending and receiving data 
 * Returns:
 *   ft_ping_usage function
*/
static int  ft_pg_exec_init_pckt( t_pg_opts opts, t_pg_sock *sock)
{
	t_icmphdr	*hdr;
	int i;

	sock->pckt_send.msg_len = FT_ICMPHDR_LEN + opts.packetsize;
	sock->pckt_send.msg = (char *)ft_memalloc(sock->pckt_send.msg_len);
	if (sock->pckt_send.msg == NULL)
		return (FT_EXFAIL);
	hdr = (t_icmphdr *)&sock->pckt_send.msg[0];
	i = FT_ICMPHDR_LEN;

	hdr->type = ICMP_ECHO;
	hdr->un.echo.id = sock->id;
	hdr->un.echo.sequence = 0;
	hdr->checksum = 0;

	while (i < (sock->pckt_send.msg_len  - 1))
		sock->pckt_send.msg[i++] = i + '0';
	sock->pckt_send.msg[i] = 0;

	ft_memset(&sock->pckt_recv, 0, sizeof(sock->pckt_recv));
	sock->pckt_recv.msg_len = FT_PING_ICMPHDR + opts.packetsize;
	sock->pckt_recv.msg = (char *)ft_memalloc(sock->pckt_recv.msg_len);
	if (sock->pckt_recv.msg == NULL) {
		free(sock->pckt_send.msg);
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
static int  ft_pg_exec_init_sock(t_pg_opts opts, t_pg_sock *sock)
{	
	t_addrinfo 	addrinfo;
	t_timeval		tv;

	ft_memset(&addrinfo, 0, sizeof(addrinfo));
	ft_memset(&tv, 0, sizeof(tv));
	tv.tv_sec = 1;

	if (ft_sock_getaddrinfo(opts.dest, &addrinfo) == EXIT_FAILURE) {
		fprintf(stderr, "%s: Échec temporaire dans la résolution du nom\n", opts.dest);
		return (FT_EXFAIL);
	}

	sock->id = getpid() & 0xFFFF;
	sock->fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP);
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

  if (setsockopt(sock->fd, FT_SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv)) != 0)
		if (opts.verbose == 1)
			fprintf(stderr, "Set RECVTIMEOUT option failed.\n");

	return (EXIT_SUCCESS);
}

int  ft_ping_exec_init(t_pg_opts opts, t_pg_sock *sock, t_pg_stats *stats)
{	
	char ip[FT_ADDRSTRLEN];

	if (!(getuid() == 0))
		if (opts.verbose)
			fprintf(stderr, "No privileges \n");
	
	if (ft_pg_exec_init_sock(opts, sock) == FT_EXFAIL)
		return (FT_EXFAIL);

	if (ft_pg_exec_init_pckt(opts, sock) == FT_EXFAIL)
		return (FT_EXFAIL);

	if (ft_sock_ntop((t_in_addr *)&sock->addrin.sin_addr, ip) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	printf("PING %s (%s) %d(%ld) bytes of data.\n",
		opts.dest, ip, opts.packetsize, opts.packetsize + FT_PING_ICMPHDR);

	ft_sock_gettime(&stats->time.start);

	return (EXIT_SUCCESS);
}


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