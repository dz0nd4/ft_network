/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/19 15:49:12 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int g_ping_run = 1;
int g_ping_send = 1;

#define RECV_TIMEOUT 1

static int  ft_ping_exec_init(const char *dst, t_pg_sock *sock, t_pg_opts opts)
{	
	sock->id = getpid() & 0xFFFF;

	if (ft_socket_getaddrinfo(dst, &sock->addrinfo) == EXIT_FAILURE)
		return (ft_ping_error_host(dst));

	sock->fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP);

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

	signal(SIGINT, ft_ping_exec_sigint);
	signal(SIGALRM, ft_ping_exec_sigarlm);

	return (EXIT_SUCCESS);
}

int  ft_ping_exec(const char *dst, t_pg_opts opts)
{
	t_pg_sock	sock;
	t_pg_stats stats;

	ft_memset(&sock, 0, sizeof(sock));
	ft_memset(&stats, 0, sizeof(stats));

	ft_ping_exec_init(dst, &sock, opts);

	ft_ping_exec_print_infos(dst, sock);
	
	ft_sock_gettime(&stats.time.start);
	while (g_ping_run) {
		if (ft_ping_exec_send(&sock, opts, &stats) ==  FT_EXFAIL)
			return (FT_EXFAIL);
		ft_ping_exec_receive(sock, &stats);
		ft_sock_delay();
	}
	ft_sock_gettime(&stats.time.stop);

	ft_ping_exec_print_stats(dst, stats);

	return(EXIT_SUCCESS);
}
