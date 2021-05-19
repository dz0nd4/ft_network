/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_send.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/19 15:45:05 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int		ft_ping_exec_send(t_pg_sock *sock, t_pg_opts opts, t_pg_stats *stats)
{	
	int i;
	t_pg_pckt	pckt;

	i = 0;
	ft_memset(&pckt, 0, sizeof(t_pg_pckt));
	
	pckt.hdr.type = ICMP_ECHO;
	pckt.hdr.un.echo.id = sock->id;
	for ( i = 0; i < sizeof(pckt.msg); i++ )
		pckt.msg[i] = i+'0';
	pckt.msg[i] = 0;
	sock->pckt.hdr.un.echo.sequence = stats->nbPcktSend + 1;
	sock->pckt.hdr.checksum = ft_sock_cksum(&pckt, sizeof(pckt));

	ft_sock_gettime(&g_ctx.time.start);
	if (ft_socket_send(sock->fd, (char *)&sock->pckt, PACKETSIZE,
			(t_sockaddr_in *)sock->addrinfo.ai_addr) == FT_EXFAIL)
		return (FT_EXFAIL);

	stats->nbPcktSend += 1;

	return (FT_EXOK);
}
