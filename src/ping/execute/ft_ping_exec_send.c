/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_send.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/18 23:09:45 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int		ft_ping_exec_send(t_pg_sock sock, t_pg_opts opts, t_pg_stats *stats)
{	
	int i;
	t_pg_pckt		packet;
	
	i = 0;

	ft_memset(&packet, 0, sizeof(t_pg_pckt));

	packet.icmp.icmp_type = ICMP_ECHO;
	packet.icmp.icmp_code = 0;
	packet.icmp.icmp_cksum = 0;
	packet.icmp.icmp_seq = stats->nbPcktSend + 1;
	packet.icmp.icmp_id = sock.id;

	for (i = 0; i < sizeof(packet.msg); i++)
		packet.msg[i] = i;
	packet.msg[i] = 0;

	packet.icmp.icmp_cksum = ft_sock_cksum(&packet, PACKETSIZE);

	ft_sock_gettime(&g_ctx.time.start);
	if (ft_socket_send(sock.fd, (char *)&packet, PACKETSIZE,
			(t_sockaddr_in *)sock.addrinfo.ai_addr) == FT_EXFAIL)
		return (FT_EXFAIL);

	stats->nbPcktSend += 1;

	return (FT_EXOK);
}
