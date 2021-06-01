/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_recv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 22:41:36 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

/*
 * ft_ping_exec_send
 *
 * Description:
 *   Clear msg pckt_recv
 * Returns:
 *   FT_EXOK or FT_EXFAIL if ft_recvmsg fails
*/
int		ft_ping_exec_receive(t_pg_sock *sock, t_pg_opts opts, t_pg_stats *stats)
{
    int fd;
    t_pg_pckt_recv *pckt_recv;
    t_icmphdr *hdr;

    fd = sock->fd;
    pckt_recv = &sock->pckt_recv;

    ft_memset(pckt_recv->addr, 0, sizeof(pckt_recv->addr));
    ft_memset(pckt_recv->msg, 0, sizeof(pckt_recv->msg_len));

    hdr = (t_icmphdr *)&pckt_recv->msg[FT_IPHDR_LEN];
    hdr->un.echo.id = 0;

    while (hdr->un.echo.id != sock->id) {
        pckt_recv->cc = ft_recvmsg(fd, pckt_recv->addr, pckt_recv->msg, pckt_recv->msg_len);
        if (pckt_recv->cc <= 0) {
            if (opts.verbose)
                fprintf(stderr, "Request timeout for icmp_seq %u\n", stats->nbPcktSend);
            return (FT_EXFAIL);
        }
    }

    return (FT_EXOK);
}
