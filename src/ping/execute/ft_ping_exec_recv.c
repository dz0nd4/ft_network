/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_recv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/20 19:01:30 by user42           ###   ########lyon.fr   */
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
// int		ft_ping_exec_recv_echo_recply(t_pg_sock *sock, t_pg_opts opts, t_pg_stats *stats)
// {
//     t_ip *ip;
//     t_icmphdr *hdr;
//     double elapsedTime;

//     ip = (t_ip  *)sock->pckt_recv;
//     hdr = (t_icmphdr *)&sock->pckt_recv[FT_IPHDR_LEN];
//     elapsedTime = 0;

//     stats->nbPcktReceive += 1;

//     if (opts.packetsize >= sizeof(t_timeval)) {
//         t_timeval stop;
//         ft_sock_gettime(&stop);
//         elapsedTime = ft_sock_timediff(&stop, (t_timeval *)&sock->pckt_recv[28]);
//     }
        
//         int ttl = ip->ip_ttl;
//         int seq = hdr->un.echo.sequence;
//         ft_ping_exec_print_pckt(cc - sizeof(t_ip), addr, seq, ttl, elapsedTime);
// }

int		ft_ping_exec_recv_unpack(t_pg_sock *sock, t_pg_stats *stats, int cc, char *addr)
{
    t_ip *ip;
    t_icmphdr *hdr;
    double elapsedTime;

    ip = (t_ip  *)sock->recv_pckt;
    hdr = (t_icmphdr *)&sock->recv_pckt[FT_IPHDR_LEN];
    elapsedTime = 0;
    if (hdr->un.echo.id != sock->id)
        return FT_EXFAIL; //return (ft_ping_err_exec_recv("Bad packet id\n"));

    if (hdr->type == ICMP_ECHOREPLY) {
        elapsedTime = ft_sock_getelapsedtime((t_timeval *)&sock->recv_pckt[28]);
        ft_ping_exec_print_pckt(cc - sizeof(t_ip), addr, hdr->un.echo.sequence,
                                    ip->ip_ttl, elapsedTime);
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
    if (ft_sock_cksum((unsigned short *)sock->recv_pckt, cc))
        return (ft_ping_err_exec_recv("Bad checksum\n"));

    ft_ping_exec_recv_unpack(sock, stats, cc, addr);
    // ip = (t_ip  *)sock->recv_pckt;
    // hdr = (t_icmphdr *)&sock->recv_pckt[FT_IPHDR_LEN];

    // if (hdr->un.echo.id != sock->id)
    //     return (ft_ping_err_exec_recv("Bad packet id\n"));

    // if (hdr->type == ICMP_ECHOREPLY) {
    //     // ft_ping_exec_print_pckt(cc - sizeof(t_ip), addr, hdr->un.echo.sequence,
    //     //                             ip->ip_ttl, elapsedTime);

    // } else if (hdr->type == ICMP_TIME_EXCEEDED) {
        
    // }
    // ft_ping_exec_unpack((t_ip *)sock->pckt_recv, (t_icmphdr *)&sock->pckt_recv[20], &sock->pckt_recv[28]);


    // t_pg_pckt *pckt = (t_pg_pckt *)&sock->pckt_recv[20];

    // if (pckt->hdr.un.echo.id != sock->id) {
    //     fprintf(stderr, "Bad packet id\n");
    //     return (FT_EXFAIL);
    // }

    // // hexdump(&packet[28], sizeof(t_timeval));

    // if (pckt->hdr.type == ICMP_ECHOREPLY) {
    //     stats->nbPcktReceive += 1;
    //     t_timeval start;
    //     t_timeval stop;

    //     ft_memcpy(&start, &sock->pckt_recv[28], sizeof(t_timeval));
    //     ft_sock_gettime(&stop);
    //     // double socktime = ft_sock_time(start, stop);
    //     // printf("start: %ld %ld | stop: %ld %ld\n", start.tv_sec, start.tv_usec, stop.tv_sec, stop.tv_usec);
    //     double elapsedTime = tvsub(&stop, &start);
    //     // printf("stop: %ld %ld\n", stop.tv_sec, stop.tv_usec);
    //     // int triptime = stop.tv_sec*1000+(stop.tv_usec/1000);
    //     // printf("triptime : %d\n", triptime);
        
    //     t_ip *ip = (t_ip *)sock->pckt_recv;
    //     int ttl = ip->ip_ttl;
    //     int seq = pckt->hdr.un.echo.sequence;

    //     // ft_sock_gettime(&g_ctx.time.stop);
    //     // double time = ft_ping_execute_recv_print_time(&g_ctx.time);
    //     // ft_ping_execute_calc_rtt(time);
    //     ft_ping_exec_print_pckt(cc - sizeof(t_ip), addr, seq, ttl, elapsedTime);
    //     // ft_ping_exec_print_pckt(cc - sizeof(t_ip), addr, packet, elapsedTime);

    // } else if (pckt->hdr.type == ICMP_TIME_EXCEEDED) {
    //     int seq = pckt->hdr.un.echo.sequence;
    //     printf("From : Unknow icmp_seq=%d Time to live exceeded\n", seq);
    // }
    // else {
    //     fprintf(stderr, "Received %s\n", strerror(errno));
    // }

    // printf("\n -- \n");


    return cc;
}


// int		ft_ping_exec_receive(t_pg_sock *sock, t_pg_stats *stats)
// {
//     char addr[128];
//     int cc;
//     t_tr_pack_hdr_icmp *hdr_icmp;


//     cc = ft_sock_recvmsg(sock->fd, addr, sock->pckt_recv, FT_PING_ICMPHDR + 56);
//     if (cc <= 0)
//         return (-1);
    
//     hdr_icmp = (t_tr_pack_hdr_icmp *)sock->pckt_recv;
//     // t_icmphdr *icp = (t_icmphdr *)hdr_icmp->icmp;


//     if (ft_sock_cksum((unsigned short *)hdr_icmp, cc)) {
//         fprintf(stderr, "Bad checksum.\n");
//         return (-1);
//     }


//     t_pg_pckt *pckt = (t_pg_pckt *)&sock->pckt_recv[20];

//     if (pckt->hdr.un.echo.id != sock->id) {
//         fprintf(stderr, "Bad packet id\n");
//         return (FT_EXFAIL);
//     }

//     // hexdump(&packet[28], sizeof(t_timeval));

//     if (pckt->hdr.type == ICMP_ECHOREPLY) {
//         stats->nbPcktReceive += 1;


//     	// struct iphdr *ip = packet;
// 	    // struct icmphdr *icmp = packet+ip->ihl*4;

//         // printf("iphl: %d\n", packet+ip->ihl*4);
	    
//         // printf("IPv%d: hdr-size=%d pkt-size=%d protocol=%d TTL=%d\n",
// 		//     ip->version, ip->ihl*4, ntohs(ip->tot_len), ip->protocol,
// 		//     ip->ttl);
//         //     if ( icmp->un.echo.id == sock->id)
//         //     {
//         //         printf("ICMP: type[%d/%d] checksum[%d] id[%d] seq[%d]\n",
//         //             icmp->type, icmp->code, ntohs(icmp->checksum),
//         //             icmp->un.echo.id, icmp->un.echo.sequence);
//         //     }
            
//         t_timeval start;
//         t_timeval stop;

//         ft_memcpy(&start, &sock->pckt_recv[28], sizeof(t_timeval));
//         ft_sock_gettime(&stop);
//         // double socktime = ft_sock_time(start, stop);
//         // printf("start: %ld %ld | stop: %ld %ld\n", start.tv_sec, start.tv_usec, stop.tv_sec, stop.tv_usec);
//         double elapsedTime = tvsub(&stop, &start);
//         // printf("stop: %ld %ld\n", stop.tv_sec, stop.tv_usec);
//         // int triptime = stop.tv_sec*1000+(stop.tv_usec/1000);
//         // printf("triptime : %d\n", triptime);
        
//         t_ip *ip = (t_ip *)sock->pckt_recv;
//         int ttl = ip->ip_ttl;
//         int seq = pckt->hdr.un.echo.sequence;

//         // ft_sock_gettime(&g_ctx.time.stop);
//         // double time = ft_ping_execute_recv_print_time(&g_ctx.time);
//         // ft_ping_execute_calc_rtt(time);
//         ft_ping_exec_print_pckt(cc - sizeof(t_ip), addr, seq, ttl, elapsedTime);
//         // ft_ping_exec_print_pckt(cc - sizeof(t_ip), addr, packet, elapsedTime);

//     } else if (pckt->hdr.type == ICMP_TIME_EXCEEDED) {
//         int seq = pckt->hdr.un.echo.sequence;
//         printf("From : Unknow icmp_seq=%d Time to live exceeded\n", seq);
//     }
//     else {
//         fprintf(stderr, "Received %s\n", strerror(errno));
//     }

//     // printf("\n -- \n");


//     return cc;
// }
