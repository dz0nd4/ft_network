/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_recv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 14:43:06 by user42           ###   ########lyon.fr   */
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

int		ft_ping_exec_unpack(t_ip *ip, t_icmphdr *icmp, unsigned char *data)
{
    if (icmp->type == ICMP_ECHOREPLY)
        printf("echo reply\n");
    else
        printf('not an echo reply\n');
    return (FT_EXOK);
}


int		ft_ping_exec_recv_unpack(t_pg_sock *sock, t_pg_stats *stats, int cc, char *addr)
{
    t_ip *ip;
    t_icmphdr *hdr;
    t_icmp *icmp;
    double elapsedTime;

    ip = (t_ip  *)sock->recv_pckt;
    hdr = (t_icmphdr *)&sock->recv_pckt[FT_IPHDR_LEN];
    icmp = (t_icmp *)&sock->recv_pckt[FT_IPHDR_LEN];


    elapsedTime = 0;
    // if (hdr->un.echo.id != sock->id)
    //     return FT_EXFAIL; //return (ft_ping_err_exec_recv("Bad packet id\n"));

    if (hdr->type == ICMP_ECHOREPLY) {
        elapsedTime = ft_sock_getelapsedtime((t_timeval *)&sock->recv_pckt[28]);
        ft_ping_exec_print_pckt(cc - sizeof(t_ip), addr, hdr->un.echo.sequence,
                                    ip->ip_ttl, elapsedTime);
        ft_ping_execute_calc_rtt(elapsedTime);
        stats->nbPcktReceive += 1;
    } else {
        ft_pg_exec_print_pckt(addr, hdr->un.echo.sequence, hdr->type);
    }
}

int		ft_ping_exec_receive(t_pg_sock *sock, t_pg_opts opts, t_pg_stats *stats)
{
    char addr[128];
    int cc;

    ft_memset(addr, 0, sizeof(addr));
    ft_memset(sock->recv_pckt, 0, sock->recv_pckt_len);

    cc = ft_sock_recvmsg(sock->fd, addr, sock->recv_pckt, sock->recv_pckt_len);
    if (cc <= 0)
        return (-1);
    // if (ft_sock_cksum((unsigned short *)sock->recv_pckt, cc))
    //     return (ft_ping_err_exec_recv("Bad checksum\n"));

    ft_ping_exec_recv_unpack(sock, stats, cc, addr);

    return cc;
}
