/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/07/27 13:54:33 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

/*
 * ft_pg_exec_init_pckt
 *
 * Description:
 *   Dynamic allocate packets for sending and receiving data
 * Returns:
 *   ft_ping_usage function
 */
// static int ft_pg_exec_init_pckt(t_pg_opts opts, t_pg_sock *sock) {
//   int i;

//   // ft_memset(&sock->pckt_send, 0, sizeof(sock->pckt_send));
//   // sock->pckt_send.msg_len = FT_PING_HDR + opts.packetsize;
//   // sock->pckt_send.msg = (char *)ft_memalloc(sock->pckt_send.msg_len);
//   // if (sock->pckt_send.msg == NULL) return (FT_EXFAIL);

//   // ft_sock_pckt_icmp(sock->pckt_send.msg, sock->pckt_send.msg_len,
//   //                   sock->pckt_send.addrin);

//   // ft_memset(&sock->pckt_recv, 0, sizeof(sock->pckt_recv));
//   // sock->pckt_recv.msg_len = FT_PING_HDR + opts.packetsize;
//   // sock->pckt_recv.msg = (char *)ft_memalloc(sock->pckt_recv.msg_len);
//   // if (sock->pckt_recv.msg == NULL) {
//   //   free(sock->pckt_send.msg);
//   //   return (FT_EXFAIL);
//   // }

//   return (FT_EXOK);
// }

// /*
//  * ft_pg_exec_init_sock
//  *
//  * Description:
//  *   Function for initialize the socket && target info
//  * Returns:
//  *
//  */
// static int ft_pg_exec_init_sock(t_pg_opts opts, t_pg_sock *sock) {
//   t_addrinfo addrinfo;

//   ft_memset(&addrinfo, 0, sizeof(t_addrinfo));
//   addrinfo.ai_family = AF_INET;
//   addrinfo.ai_socktype = SOCK_DGRAM;

//   if (ft_getaddrinfo(opts.dest, &addrinfo) == FT_EXFAIL) {
//     fprintf(stderr, "ping: cannot resolve %s: Unknown host\n", opts.dest);
//     return (FT_EXFAIL);
//   }

//   sock->fd = socket(addrinfo.ai_family, addrinfo.ai_socktype, IPPROTO_ICMP);

//   if (sock->fd == INVALID_SOCKET) {
//     if (opts.verbose)
//       fprintf(stderr,
//               "ping: socket: Permission denied, attempting raw socket...\n");

//     ft_memset(&addrinfo, 0, sizeof(t_addrinfo));
//     addrinfo.ai_family = AF_INET;
//     addrinfo.ai_socktype = SOCK_RAW;
//     addrinfo.ai_protocol = IPPROTO_ICMP;

//     if (ft_getaddrinfo(opts.dest, &addrinfo) == FT_EXFAIL) {
//       fprintf(stderr, "ping: cannot resolve %s: Unknown host\n", opts.dest);
//       return (FT_EXFAIL);
//     }

//     sock->fd = ft_socket_icmp();
//     // sock->fd = socket(addrinfo.ai_family, addrinfo.ai_socktype,
//     // IPPROTO_ICMP);
//     if (sock->fd == INVALID_SOCKET) {
//       fprintf(stderr, "ping: socket: Permission denied for raw socket\n");
//       return (FT_EXFAIL);
//     }
//   }

//   ft_setsockopt_ttl(&sock->fd, opts.ttl, opts.verbose);
//   ft_setsockopt_sndtimeo(&sock->fd, 1, opts.verbose);
//   ft_setsockopt_rcvtimeo(&sock->fd, 1, opts.verbose);
//   ft_memcpy(&sock->pckt_send.addrin, addrinfo.ai_addr, sizeof(t_sockaddr));

//   return (FT_EXOK);
// }

// int ft_ping_exec_init(t_pg_opts opts, t_pg_sock *sock, t_pg_stats *stats) {
//   if (!(getuid() == 0))
//     fprintf(stderr,
//             "/!\\ You are running this program without privileges ! /!\\
//             \n");

//   sock->id = getpid() & 0xFFFF;

//   // if (ft_pg_exec_init_pckt(opts, sock) == FT_EXFAIL) return (FT_EXFAIL);
//   if (ft_pg_exec_init_sock(opts, sock) == FT_EXFAIL) return (FT_EXFAIL);

//   ft_gettimeofday(&stats->start);

//   return (FT_EXOK);
// }
