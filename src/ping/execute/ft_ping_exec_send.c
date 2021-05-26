/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_send.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 16:50:31 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

/*
 * ft_ping_exec_send
 *
 * Description:
 *   Modify header of pckt_send: sequence, timeval & checksum
 * Returns:
 *   FT_EXOK or FT_EXFAIL if ft_sock_send fails
*/
int		ft_ping_exec_send(t_pg_sock *sock, t_pg_opts opts, t_pg_stats *stats)
{
	t_icmphdr	*hdr;
	t_timeval *tv;

	hdr = (t_icmphdr *)&sock->pckt_send.msg[0];
	tv = (t_timeval *)&sock->pckt_send.msg[FT_ICMPHDR_LEN];

	hdr->un.echo.sequence = stats->nbPcktSend + 1;
	hdr->checksum = 0;

	if (opts.packetsize >= sizeof(t_timeval)) {
		ft_memset(&sock->pckt_send.msg[FT_ICMPHDR_LEN], 0, sizeof(t_timeval));
		ft_sock_gettime(tv);
	}

	hdr->checksum = ft_sock_cksum(sock->pckt_send.msg, sock->pckt_send.msg_len);

	if (ft_sock_send(sock->fd, sock->pckt_send.msg, sock->pckt_send.msg_len,
			&sock->addrin) == FT_EXFAIL)
		return (FT_EXFAIL);
	
	stats->nbPcktSend += 1;
	return (FT_EXOK);
}
