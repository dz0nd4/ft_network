/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_send.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 15:02:40 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int		ft_ping_exec_send(t_pg_sock *sock, t_pg_opts opts, t_pg_stats *stats)
{
	t_icmphdr	*hdr;
	t_timeval *tv;

	hdr = (t_icmphdr *)&sock->send_pckt[0];
	tv = (t_timeval *)&sock->send_pckt[FT_ICMPHDR_LEN];
	hdr->un.echo.sequence = stats->nbPcktSend + 1;
	hdr->checksum = 0;

	// printf("%u \n", stats->nbPcktSend);

	if (opts.packetsize >= sizeof(t_timeval)) {
		ft_memset(&sock->send_pckt[FT_ICMPHDR_LEN], 0, sizeof(t_timeval));
		ft_sock_gettime(tv);
	}

	hdr->checksum = ft_sock_cksum(sock->send_pckt, sock->send_pckt_len);

	if (ft_sock_send(sock->fd, sock->send_pckt, sock->send_pckt_len,
			&sock->addrin) == FT_EXFAIL)
		return (FT_EXFAIL);

	stats->nbPcktSend += 1;

	return (FT_EXOK);
}
