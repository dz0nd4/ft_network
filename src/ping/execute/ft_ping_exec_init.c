/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 18:49:12 by dzonda           ###   ########lyon.fr   */
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
	t_timeval *tv;
	int i;

	sock->pckt_send.msg_len = FT_ICMPHDR_LEN + opts.packetsize;
	sock->pckt_send.msg = (char *)ft_memalloc(sock->pckt_send.msg_len);
	if (sock->pckt_send.msg == NULL)
		return (FT_EXFAIL);
	hdr = (t_icmphdr *)&sock->pckt_send.msg[0];
	tv = (t_timeval *)&sock->pckt_send.msg[FT_ICMPHDR_LEN];
	i = FT_ICMPHDR_LEN;

	hdr->type = ICMP_ECHO;
	hdr->un.echo.id = getpid() & 0xFFFF;
	hdr->un.echo.sequence = 0;
	hdr->checksum = 0;

	while (i < (sock->pckt_send.msg_len  - 1))
		sock->pckt_send.msg[i++] = i + '0';
	sock->pckt_send.msg[i] = 0;


	if (opts.packetsize >= sizeof(t_timeval)) {
		ft_memset(&sock->pckt_send.msg[FT_ICMPHDR_LEN], 0, sizeof(t_timeval));
		ft_sock_gettime(tv);
	}

	hdr->checksum = ft_sock_cksum(sock->pckt_send.msg, sock->pckt_send.msg_len);

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
 *   Function for fix the bug on MacOS with getaddrinfo
 * Returns:
 * 
*/
static int  	ft_pg_exec_init_sock(t_pg_opts opts, t_pg_sock *sock)
{	
	int 				timeout;
	t_addrinfo 	addrinfo;
	
	timeout = 30;
	ft_memset(&addrinfo, 0, sizeof(t_addrinfo));
	addrinfo.ai_family = AF_INET;
	addrinfo.ai_socktype = SOCK_DGRAM;

	while (timeout--) {
		if (ft_sock_getaddrinfo(opts.dest, &addrinfo) == FT_EXFAIL)
			return (FT_EXFAIL);

		sock->fd = socket(addrinfo.ai_family, addrinfo.ai_socktype, IPPROTO_ICMP);
		ft_setsockopt_ttl(&sock->fd, opts.ttl, opts.verbose);
		ft_setsockopt_sndtimeo(&sock->fd, 1, opts.verbose);
		ft_setsockopt_rcvtimeo(&sock->fd, 1, opts.verbose);

		if (sock->fd == INVALID_SOCKET) {
			if (opts.verbose && timeout == 29)
				fprintf(stderr, "ping: socket: Permission denied, attempting raw socket...\n");
			addrinfo.ai_family = AF_INET;
			addrinfo.ai_socktype = SOCK_RAW;
		} else {
			ft_memcpy(&sock->addrin, addrinfo.ai_addr, sizeof(t_sockaddr));
			if (ft_sock_send(sock->fd, sock->pckt_send.msg, sock->pckt_send.msg_len, &sock->addrin) == FT_EXOK)
				if (ft_sock_recvmsg(sock->fd, sock->pckt_recv.addr, sock->pckt_recv.msg, sock->pckt_recv.msg_len) > 0)
					return (FT_EXOK);
			close(sock->fd);
		}
	}

	return (FT_EXFAIL);
}

int  ft_ping_exec_init(t_pg_opts opts, t_pg_sock *sock, t_pg_stats *stats)
{	
	char ip[FT_ADDRSTRLEN];

	if (!(getuid() == 0))
		if (opts.verbose)
			fprintf(stderr, "No privileges \n");
	
	sock->id = getpid() & 0xFFFF;

	if (ft_pg_exec_init_pckt(opts, sock) == FT_EXFAIL)
		return (FT_EXFAIL);

	if (ft_pg_exec_init_sock(opts, sock) == FT_EXFAIL) {
		fprintf(stderr, "%s: Échec temporaire dans la résolution du nom\n", opts.dest);
		return (FT_EXFAIL);
	}

	if (ft_sock_ntop((t_in_addr *)&sock->addrin.sin_addr, ip) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	printf("PING %s (%s) %d(%ld) bytes of data.\n",
		opts.dest, ip, opts.packetsize, opts.packetsize + FT_PING_ICMPHDR);

	ft_sock_gettime(&stats->time.start);

	return (EXIT_SUCCESS);
}
