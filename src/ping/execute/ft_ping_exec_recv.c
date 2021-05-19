/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_recv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/19 15:33:05 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

double   ft_ping_execute_recv_print_time(t_tr_time *time)
{
  double start = (time->start.tv_sec) * 1000 + (time->start.tv_usec) / 1000;
  double stop = (time->stop.tv_sec) * 1000 + (time->stop.tv_usec) / 1000 ;
  double dt = stop - start;
  return dt;
}

int     ft_ping_execute_calc_rtt(double time)
{
    t_pg_stats *stats = &g_ctx.stats;

    if (stats->minTime == 0 || time < stats->minTime)
        stats->minTime = time;
    if (time > stats->maxTime)
        stats->maxTime = time;
    
    stats->avgTime += time;

    return 0;
}

int		ft_ping_execute_receive_init(t_pg_msg *msg)
{
    t_iovec *iov;
    t_msghdr *msghdr;

    iov = &msg->iov;
    msghdr = &msg->msg;
    ft_memset(msg, 0, sizeof(*msg));
    
    iov->iov_base = msg->packet;
    iov->iov_len = sizeof(msg->packet);
    msghdr->msg_name = msg->addrbuf;
    msghdr->msg_namelen = sizeof(msg->addrbuf);
    msghdr->msg_iov = iov;
    msghdr->msg_iovlen = 1;
    return (FT_EXOK);
}

int		ft_ping_exec_receive(t_pg_sock sock, t_pg_stats *stats)
{
    char packet[400];
    int packetlen = 400;
    char addr[128];
    int cc;
    t_tr_pack_hdr_icmp *hdr_icmp;

    cc = ft_sock_recvmsg(sock.fd, addr, packet, packetlen);
    if (cc <= 0)
        return (-1);
    
    hdr_icmp = (t_tr_pack_hdr_icmp *)packet;
    if (ft_sock_cksum((unsigned short *)hdr_icmp, cc)) {
        fprintf(stderr, "Bad checksum.\n");
        return (-1);
    }

    if (hdr_icmp->icmp.icmp_type == ICMP_ECHOREPLY) {
        stats->nbPcktReceive += 1;

        ft_sock_gettime(&g_ctx.time.stop);
        double time = ft_ping_execute_recv_print_time(&g_ctx.time);
        ft_ping_execute_calc_rtt(time);
        ft_ping_exec_print_pckt(cc - sizeof(t_ip), addr, packet, time);

    } else {
        fprintf(stderr, "Received %s\n", strerror(errno));
    }

    return cc;
}
