/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_recv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/19 21:26:49 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

/*
 * 			T V S U B
 * 
 * Subtract 2 timeval structs:  out = out - in.
 * 
 * Out is assumed to be >= in.
 */
double tvsub(t_timeval *out, t_timeval *in)
{
	// if( (out->tv_usec -= in->tv_usec) < 0 )   {
	// 	out->tv_sec--;
	// 	out->tv_usec += 1000000;
	// }
	// out->tv_sec -= in->tv_sec;

    double elapsedTime = (out->tv_sec - in->tv_sec) * 1000.0;      
    elapsedTime += (out->tv_usec - in->tv_usec) / 1000.0;  
    // printf("elapsed %f\n", elapsedTime);
    return elapsedTime;
}

double   ft_ping_execute_recv_print_time(t_tr_time *time)
{
  double start = (time->start.tv_sec) * 1000 + (time->start.tv_usec) / 1000;
  double stop = (time->stop.tv_sec) * 1000 + (time->stop.tv_usec) / 1000 ;
  double dt = stop - start;
  return dt;
}

double   ft_sock_time(t_timeval start, t_timeval stop)
{
  double dtstart = (start.tv_sec) * 1000 + (start.tv_usec) / 1000;
  double dtstop = (stop.tv_sec) * 1000 + (stop.tv_usec) / 1000 ;
  double dt = dtstop - dtstart;
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
    // t_icmphdr *icp = (t_icmphdr *)hdr_icmp->icmp;


    if (ft_sock_cksum((unsigned short *)hdr_icmp, cc)) {
        fprintf(stderr, "Bad checksum.\n");
        return (-1);
    }

    t_pg_pckt *pckt = (t_pg_pckt *)&packet[20];

    // hexdump(&packet[28], sizeof(t_timeval));

    if (pckt->hdr.type == ICMP_ECHOREPLY) {
        stats->nbPcktReceive += 1;


    	// struct iphdr *ip = packet;
	    // struct icmphdr *icmp = packet+ip->ihl*4;

        // printf("iphl: %d\n", packet+ip->ihl*4);
	    
        // printf("IPv%d: hdr-size=%d pkt-size=%d protocol=%d TTL=%d\n",
		//     ip->version, ip->ihl*4, ntohs(ip->tot_len), ip->protocol,
		//     ip->ttl);
        //     if ( icmp->un.echo.id == sock.id)
        //     {
        //         printf("ICMP: type[%d/%d] checksum[%d] id[%d] seq[%d]\n",
        //             icmp->type, icmp->code, ntohs(icmp->checksum),
        //             icmp->un.echo.id, icmp->un.echo.sequence);
        //     }
            
        t_timeval start;
        t_timeval stop;

        ft_memcpy(&start, &packet[28], sizeof(t_timeval));
        ft_sock_gettime(&stop);
        // double socktime = ft_sock_time(start, stop);
        // printf("start: %ld %ld | stop: %ld %ld\n", start.tv_sec, start.tv_usec, stop.tv_sec, stop.tv_usec);
        double elapsedTime = tvsub(&stop, &start);
        // printf("stop: %ld %ld\n", stop.tv_sec, stop.tv_usec);
        // int triptime = stop.tv_sec*1000+(stop.tv_usec/1000);
        // printf("triptime : %d\n", triptime);
        
        t_ip *ip = (t_ip *)packet;
        int ttl = ip->ip_ttl;
        int seq = pckt->hdr.un.echo.sequence;

        // ft_sock_gettime(&g_ctx.time.stop);
        // double time = ft_ping_execute_recv_print_time(&g_ctx.time);
        // ft_ping_execute_calc_rtt(time);
        ft_ping_exec_print_pckt(cc - sizeof(t_ip), addr, seq, ttl, elapsedTime);
        // ft_ping_exec_print_pckt(cc - sizeof(t_ip), addr, packet, elapsedTime);

    } else {
        fprintf(stderr, "Received %s\n", strerror(errno));
    }

    // printf("\n -- \n");


    return cc;
}
