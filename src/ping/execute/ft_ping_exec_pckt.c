/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_pckt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 15:40:12 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int    ft_sock_getaddrinfo2(const char *host, t_addrinfo *host_addrinfo)
{
  int           sfd;
	t_addrinfo		hints;
	t_addrinfo		*result;
	t_addrinfo		*rp;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = 0; // ! should be changed for traceroute
  hints.ai_flags = AI_CANONNAME;

  if (getaddrinfo(host, NULL, (struct addrinfo *)&hints, (struct addrinfo **)&result) != 0)
    return (EXIT_FAILURE);

  rp = result;
	while (rp != NULL) {
		// sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        // if (sfd != INVALID_SOCKET)
		// 	break;
        if (rp->ai_canonname != NULL)
            break;
		rp = rp->ai_next;
	}
	if (rp == NULL)
		return (EXIT_FAILURE);
  
    // printf("cannoname: %s\n", rp->ai_canonname);

	ft_memcpy(host_addrinfo, rp, sizeof(t_addrinfo));

	close(sfd);
	freeaddrinfo((struct addrinfo *)result);

  return (EXIT_SUCCESS);
}

int     ft_ping_execute_calc_rtt(t_pg_stats *stats, double time)
{
    if (stats->minTime == 0 || time < stats->minTime)
        stats->minTime = time;
    if (time > stats->maxTime)
        stats->maxTime = time;
    
    stats->avgTime += time;

    return 0;
}

int  ft_pg_exec_recv_pckt_other(char *addr, int seq, int icmp_type)
{
    t_sockaddr_in sockaddr_in;
    char ipv4[FT_ADDRSTRLEN];
    char hostname[FT_NI_MAXHOST];

    ft_memcpy(&sockaddr_in, addr, sizeof(t_sockaddr_in));

    if (ft_sock_ntop((t_in_addr *)&sockaddr_in.sin_addr, ipv4) == EXIT_FAILURE)
	  	return (FT_EXFAIL);

    ft_sock_getnameinfo(&sockaddr_in, hostname);

    char *str_type = ft_sock_get_icmp_type(icmp_type);
    if (str_type != "Unknown type") {
      printf("From %s (%s): ", hostname, ipv4);
      printf("icmp_seq=%u %s\n", seq, str_type);
    }
		return (FT_EXOK);
}

int  ft_pg_exec_recv_pckt_other2(t_pg_pckt_recv pckt_recv, t_pg_stats *stats)
{
    t_sockaddr_in sockaddr_in;
    t_icmphdr *hdr;
    char ipv4[FT_ADDRSTRLEN];
    char hostname[FT_NI_MAXHOST];

    hdr = (t_icmphdr *)&pckt_recv.msg[FT_IPHDR_LEN];

    ft_memcpy(&sockaddr_in, pckt_recv.addr, sizeof(t_sockaddr_in));

    if (ft_sock_ntop((t_in_addr *)&sockaddr_in.sin_addr, ipv4) == EXIT_FAILURE)
	  	return (FT_EXFAIL);

    ft_sock_getnameinfo(&sockaddr_in, hostname);

    char *str_type = ft_sock_get_icmp_type(hdr->type);
    if (str_type != "Unknown type") {
      printf("From %s (%s): ", hostname, ipv4);
      printf("icmp_seq=%u %s\n", stats->nbPcktSend, str_type);
    }
		return (FT_EXOK);
}

int  ft_pg_exec_recv_prpckt_reply(t_pg_pckt_recv pckt_recv, double time, t_pg_opts opts)
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



    printf("%ld bytes from ", pckt_recv.cc - FT_IPHDR_LEN);

    if (!opts.numeric_only) {
      ft_sock_getnameinfo(&sockaddr_in, hostname);
      // t_addrinfo addrinfo;
      // if (ft_sock_getaddrinfo2(ipv4, &addrinfo) == FT_EXFAIL)
      //     printf("getaddrinfo fails\n");
      printf("%s (%s): ", hostname, ipv4);
    } else {
      printf("%s: ", ipv4);
    }

    printf("icmp_seq=%u ttl=%d ", hdr->un.echo.sequence, ip->ip_ttl);

    if (opts.packetsize >= FT_TIMEVAL_LEN)
      printf("time=%0.2f ms", time);

    printf("\n");

		return (FT_EXOK);
}

int  ft_ping_exec_pckt(t_pg_sock *sock, t_pg_opts opts, t_pg_stats *stats)
{
    t_icmphdr *hdr;
    t_timeval *tv;
    double elapsed_time;
  
    hdr = (t_icmphdr *)&sock->pckt_recv.msg[FT_IPHDR_LEN];
    tv = (t_timeval *)&sock->pckt_recv.msg[FT_PING_ICMPHDR];
    elapsed_time = 0;

    if (hdr->un.echo.id == sock->id && hdr->type == ICMP_ECHOREPLY) {
        if (opts.packetsize >= FT_TIMEVAL_LEN) {
            elapsed_time = ft_sock_getelapsedtime(tv);
            ft_ping_execute_calc_rtt(stats, elapsed_time);
        }
        ft_pg_exec_recv_prpckt_reply(sock->pckt_recv, elapsed_time, opts);
        stats->nbPcktReceive += 1;
    } else {
        // ft_pg_exec_recv_pckt_other(sock->pckt_recv.addr, hdr->un.echo.sequence, hdr->type);
      ft_pg_exec_recv_pckt_other2(sock->pckt_recv, stats);
    }

    return (FT_EXOK);
}