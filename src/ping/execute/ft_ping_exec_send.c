/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_send.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/19 21:26:41 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int		ft_ping_exec_send(t_pg_sock *sock, t_pg_opts opts, t_pg_stats *stats)
{
	int i;
	t_pg_pckt	pckt;
	t_timeval	tv;

	i = 8;
	
	ft_memset(&pckt, 0, sizeof(t_pg_pckt));
	int len = FT_ICMPHDR_LEN + opts.packetsize;
	pckt.msg = (char *)ft_memalloc(FT_ICMPHDR_LEN + opts.packetsize);
	if (pckt.msg == NULL)
		return (FT_EXFAIL);

	t_icmphdr *hdr = &pckt.msg[0];
	hdr->type = ICMP_ECHO;
	hdr->un.echo.id = sock->id;

	if (opts.packetsize >= sizeof(t_timeval)) {
		ft_sock_gettime(&tv);
		// t_timeval *tp = pckt.msg;
		ft_memcpy(&pckt.msg[8], &tv, sizeof(t_timeval));

		// printf("start: %ld %ld\n", tv.tv_sec, tv.tv_usec);
		// hexdump(&tv, sizeof(t_timeval));
		// ft_sock_gettime(tp);
		i = 8 + sizeof(t_timeval);
	}

	while (i < opts.packetsize)
		pckt.msg[i++] = 0;
	pckt.msg[i] = 0;
	
	hdr->un.echo.sequence = stats->nbPcktSend + 1;
	hdr->checksum = ft_sock_cksum(pckt.msg, len);

	// hexdump(pckt.msg, 8 + sizeof(t_timeval));
	// printf("\n");

	ft_sock_gettime(&g_ctx.time.start);
	if (ft_socket_send(sock->fd, pckt.msg, len,
			(t_sockaddr_in *)sock->addrinfo.ai_addr) == FT_EXFAIL)
		return (FT_EXFAIL);

	free(pckt.msg);

	stats->nbPcktSend += 1;

	return (FT_EXOK);
}
// int		ft_ping_exec_send(t_pg_sock *sock, t_pg_opts opts, t_pg_stats *stats)
// {
// 	unsigned char *data;
// 	int i;
// 	t_pg_pckt	pckt;
// 	t_timeval	tv;

// 	i = 0;

// 	ft_memset(&pckt, 0, sizeof(t_pg_pckt));
// 	ft_memset(&tv, 0, sizeof(t_timeval));

// 	printf("tv : %d\n", sizeof(t_timeval));

// 	pckt.hdr.type = ICMP_ECHO;
// 	pckt.hdr.un.echo.id = sock->id;
// 	for ( i = 0; i < sizeof(pckt.msg); i++ )
// 		pckt.msg[i] = i+'0';
// 	pckt.msg[i] = 0;
// 	pckt.hdr.un.echo.sequence = stats->nbPcktSend + 1;
// 	pckt.hdr.checksum = ft_sock_cksum(&pckt, sizeof(pckt));

// 	ft_sock_gettime(&g_ctx.time.start);
// 	if (ft_socket_send(sock->fd, (char *)&pckt, PACKETSIZE,
// 			(t_sockaddr_in *)sock->addrinfo.ai_addr) == FT_EXFAIL)
// 		return (FT_EXFAIL);

// 	stats->nbPcktSend += 1;

// 	return (FT_EXOK);
// }
