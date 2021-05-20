/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_send.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/20 18:58:30 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int		ft_ping_exec_send(t_pg_sock *sock, t_pg_opts opts, t_pg_stats *stats)
{
	t_icmphdr	*hdr;
	t_timeval *tv;

	sock->send_pckt_len = FT_ICMPHDR_LEN + opts.packetsize;
	sock->send_pckt = (unsigned char *)ft_memalloc(sock->send_pckt_len);
	if (sock->send_pckt == NULL)
		return (FT_EXFAIL);
	hdr = (t_icmphdr *)&sock->send_pckt[0];
	tv = (t_timeval *)&sock->send_pckt[FT_ICMPHDR_LEN];

	hdr->type = ICMP_ECHO;
	hdr->un.echo.id = sock->id;
	hdr->checksum = 0;
	hdr->un.echo.sequence = stats->nbPcktSend + 1;

	int i = 8;

	while (i < (sock->send_pckt_len - 1))
		sock->send_pckt[i++] = i + '0';
	sock->send_pckt[i] = 0;

	if (opts.packetsize >= sizeof(t_timeval)) {
		ft_memset(&sock->send_pckt[FT_ICMPHDR_LEN], 0, sizeof(t_timeval));
		ft_sock_gettime(tv);
		i += sizeof(t_timeval);
	}



	hdr->checksum = ft_sock_cksum(sock->send_pckt, sock->send_pckt_len);

	if (ft_socket_send(sock->fd, sock->send_pckt, sock->send_pckt_len,
			&sock->addrin) == FT_EXFAIL)
		return (FT_EXFAIL);

	stats->nbPcktSend += 1;
	free(sock->send_pckt);
	return (FT_EXOK);
}
