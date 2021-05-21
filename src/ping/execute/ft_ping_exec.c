/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 13:45:07 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int g_ping_run = 1;
int g_ping_send = 1;

#define RECV_TIMEOUT 1

/*
 * ft_ping_exec_init_sock_pckt
 *
 * Description:
 *   Dynamic allocate packets for sending and receiving data 
 * Returns:
 *   ft_ping_usage function
*/
static int  ft_ping_exec_init_sock_pckt(t_pg_sock *sock, t_pg_opts opts)
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

static int  ft_ping_exec_init(const char *dst, t_pg_sock *sock, t_pg_opts opts)
{	
	t_addrinfo 	addrinfo;

	ft_memset(&addrinfo, 0, sizeof(addrinfo));

	if (ft_socket_getaddrinfo(dst, &addrinfo) == EXIT_FAILURE)
		return (ft_ping_error_host(dst));

	sock->id = getpid() & 0xFFFF;
	sock->fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP);
	ft_memcpy(&sock->addrin, addrinfo.ai_addr, sizeof(t_sockaddr_in));

  if (sock->fd == INVALID_SOCKET) {
		if (errno == EACCES && opts.verbose == 1)
			fprintf(stderr, "ping: socket: Permission denied, attempting raw socket...\n");

		sock->fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
		if (sock->fd == INVALID_SOCKET)
			return (EXIT_FAILURE);
	}

  if (setsockopt(sock->fd, SOL_IP, IP_TTL, &opts.ttl, sizeof(opts.ttl)) != 0) {
			fprintf(stderr, "Set TTL option failed.\n");
	}

	


	// sock->send_pckt_len = FT_ICMPHDR_LEN + opts.packetsize;
	// sock->send_pckt = (unsigned char *)ft_memalloc(sock->send_pckt_len);
	// if (sock->send_pckt == NULL)
	// 	return (FT_EXFAIL);
	// t_icmphdr	*hdr = (t_icmphdr *)&sock->send_pckt[0];
	// int i = 8;
	// hdr->type = ICMP_ECHO;
	// hdr->un.echo.id = sock->id;
	// hdr->un.echo.sequence = 0;
	// hdr->checksum = 0;

	// if (opts.packetsize >= sizeof(t_timeval))
	// 	i += sizeof(t_timeval);

	// while (i < (sock->send_pckt_len - 1))
	// 	sock->send_pckt[i++] = i + '0';
	// sock->send_pckt[i] = 0;

	// sock->recv_pckt_len = FT_PING_ICMPHDR + opts.packetsize;
	// sock->recv_pckt = (unsigned char *)ft_memalloc(sock->recv_pckt_len);

	return (EXIT_SUCCESS);
}

int  ft_ping_exec(const char *dst, t_pg_opts opts)
{
	t_pg_sock	*sock = &g_pg.sock;
	t_pg_stats *stats = &g_pg.stats;

	// ft_memset(&sock, 0, sizeof(sock));
	// ft_memset(&stats, 0, sizeof(stats));

	ft_ping_exec_init(dst, sock, opts);
	ft_ping_exec_init_sock_pckt(sock, opts);
	ft_ping_exec_print_infos(dst, *sock, opts);
	ft_sock_gettime(&stats->time.start);

	signal(SIGINT, ft_ping_exec_sigint);
	signal(SIGALRM, ft_ping_exec_sigarlm);
	while (g_ping_run) {
		alarm(1);
		ft_ping_exec_receive(sock, opts, stats);
		// ft_sock_delay();
	}
	// ft_sock_gettime(&stats->time.stop);

	// free(sock->pckt);

	// ft_ping_exec_print_stats(dst, *stats);

	return(EXIT_SUCCESS);
}
