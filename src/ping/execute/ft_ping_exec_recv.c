/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_recv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 23:39:37 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int     ft_ping_execute_calc_rtt(t_pg_stats *stats, double time)
{
    if (stats->minTime == 0 || time < stats->minTime)
        stats->minTime = time;
    if (time > stats->maxTime)
        stats->maxTime = time;
    
    stats->avgTime += time;

    return 0;
}

static int  ft_pg_exec_recv_pckt_other(char *addr, int seq, int icmp_type)
{
    t_sockaddr_in sockaddr_in;
    char ipv4[FT_ADDRSTRLEN];
    char hostname[FT_NI_MAXHOST];

    ft_memcpy(&sockaddr_in, addr, sizeof(t_sockaddr_in));

    if (ft_sock_ntop((t_in_addr *)&sockaddr_in.sin_addr, ipv4) == EXIT_FAILURE)
	  	return (FT_EXFAIL);

    ft_sock_getnameinfo(&sockaddr_in, hostname);

    printf("From %s (%s): ", hostname, ipv4);
    printf("icmp_seq=%u %s\n", seq, ft_sock_get_icmp_type(icmp_type));
		return (FT_EXOK);
}

static int  ft_pg_exec_recv_prpckt_reply(t_pg_pckt_recv pckt_recv, double time)
{
	  char ipv4[FT_ADDRSTRLEN];
		char hostname[FT_NI_MAXHOST];
	  t_sockaddr_in sockaddr_in;
		t_ip *ip;
    t_icmphdr *hdr;

    ft_memcpy(&sockaddr_in, pckt_recv.addr, sizeof(t_sockaddr_in));
    ip = (t_ip  *)pckt_recv.msg;
    hdr = (t_icmphdr *)&pckt_recv.msg[FT_IPHDR_LEN];
	
    if (ft_sock_ntop((t_in_addr *)&sockaddr_in.sin_addr, ipv4) == EXIT_FAILURE)
	  	return (FT_EXFAIL);

    ft_sock_getnameinfo(&sockaddr_in, hostname);

    printf("%d bytes from %s (%s): ", pckt_recv.cc - sizeof(t_ip), hostname, ipv4);
    printf("icmp_seq=%u ttl=%d, time=%0.2f ms\n", hdr->un.echo.sequence, ip->ip_ttl, time);
		return (FT_EXOK);
}


int		ft_ping_exec_receive(t_pg_sock *sock, t_pg_opts opts, t_pg_stats *stats)
{
    t_pg_pckt_recv pckt_recv;
    t_ip *ip;
    t_icmphdr *hdr;
    double elapsed_time;

    ft_memset(&pckt_recv, 0, sizeof(pckt_recv));
    pckt_recv.msg_len = sock->recv_pckt_len;
    pckt_recv.msg = sock->recv_pckt;

    pckt_recv.cc = ft_sock_recvmsg(sock->fd, pckt_recv.addr, pckt_recv.msg, pckt_recv.msg_len);
    if (pckt_recv.cc <= 0) {
        fprintf(stderr, "Request timeout for icmp_seq %u\n", stats->nbPcktSend);
        return (FT_EXFAIL);
    }
    
    hdr = (t_icmphdr *)&pckt_recv.msg[FT_IPHDR_LEN];
    elapsed_time = 0;

    if (hdr->un.echo.id == sock->id && hdr->type == ICMP_ECHOREPLY) {
        if (opts.packetsize >= FT_TIMEVAL_LEN) {
            elapsed_time = ft_sock_getelapsedtime((t_timeval *)&pckt_recv.msg[28]);
            ft_ping_execute_calc_rtt(stats, elapsed_time);
        }
        ft_pg_exec_recv_prpckt_reply(pckt_recv, elapsed_time);
        stats->nbPcktReceive += 1;
    } else if (hdr->un.echo.id == sock->id) {
        ft_pg_exec_recv_pckt_other(pckt_recv.addr, hdr->un.echo.sequence, hdr->type);
    }

    return (FT_EXOK);
}
