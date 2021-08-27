/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap_exec_send.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/26 13:39:27 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

t_uint8 ft_nmap_exec_send_tcp_flags(int scan_type) {
  if (scan_type == FT_NMAP_SCAN_SYN)
    return (FT_TCP_FLAG_SYN);
  else if (scan_type == FT_NMAP_SCAN_ACK)
    return (FT_TCP_FLAG_ACK);
  else if (scan_type == FT_NMAP_SCAN_FIN)
    return (FT_TCP_FLAG_FIN);
  else if (scan_type == FT_NMAP_SCAN_XMAS)
    return (FT_TCP_FLAG_URG | FT_TCP_FLAG_PSH | FT_TCP_FLAG_FIN);
  return (0);  // NULL
}

int ft_nmap_exec_send3(t_nmap_resps resps) {
  int fd;
  t_pckt pckt;
  t_pckt_opt opt;

  fd = ft_socket_raw();
  ft_memset(&pckt, 0, sizeof(pckt));
  ft_memset(&opt, 0, sizeof(opt));

  pckt.len = FT_IPHDR_LEN +
             (resps.key == FT_NMAP_SCAN_UDP ? FT_UDPHDR_LEN : FT_TCPHDR_LEN);
  if ((pckt.data = (t_uchar *)ft_memalloc(pckt.len)) == NULL)
    return (FT_EXFAIL);

  /* IP options */
  ft_pckt_ip_opt_default(&opt.ip);

  opt.ip.len = pckt.len;
  opt.ip.proto = resps.key == FT_NMAP_SCAN_UDP ? IPPROTO_UDP : IPPROTO_TCP;
  opt.ip.daddr = resps.in.sin_addr.s_addr;

  ft_pckt_ip_opt_set(&pckt, &opt.ip);

  if (resps.key == FT_NMAP_SCAN_UDP) {
    /* UDP options */
    ft_pckt_udp_opt_default(&opt.udp);

    opt.udp.len = pckt.len - FT_IPHDR_LEN;
    opt.udp.dport = resps.in.sin_port;

    ft_pckt_udp_opt_set(&pckt, &opt.udp);

  } else {
    /* TCP options */
    ft_pckt_tcp_opt_default(&opt.tcp);

    opt.tcp.saddr = inet_addr(resps.addr);
    opt.tcp.daddr = resps.in.sin_addr.s_addr;
    opt.tcp.dport = resps.in.sin_port;
    opt.tcp.seq = 1;

    opt.tcp.flags = ft_nmap_exec_send_tcp_flags(resps.key);

    ft_pckt_tcp_opt_set(&pckt, &opt.tcp);
  }

  int i = ft_sendto(fd, pckt.data, pckt.len, &resps.in);

  return (FT_EXOK);
}

// int ft_nmap_exec_send2(t_nmap_resp resp, int iscan) {
//   int fd;
//   t_pckt pckt;
//   t_pckt_opt opt;

//   fd = ft_socket_raw();
//   ft_memset(&pckt, 0, sizeof(pckt));
//   ft_memset(&opt, 0, sizeof(opt));

//   pckt.len = FT_IPHDR_LEN + (resp.res_scan[iscan].key == FT_NMAP_SCAN_UDP
//                                  ? FT_UDPHDR_LEN
//                                  : FT_TCPHDR_LEN);
//   if ((pckt.data = (t_uchar *)ft_memalloc(pckt.len)) == NULL)
//     return (FT_EXFAIL);

//   /* IP options */
//   ft_pckt_ip_opt_default(&opt.ip);

//   opt.ip.len = pckt.len;
//   opt.ip.proto =
//       resp.res_scan[iscan].key == FT_NMAP_SCAN_UDP ? IPPROTO_UDP :
//       IPPROTO_TCP;
//   opt.ip.daddr = resp.in.sin_addr.s_addr;

//   ft_pckt_ip_opt_set(&pckt, &opt.ip);

//   if (resp.res_scan[iscan].key == FT_NMAP_SCAN_UDP) {
//     /* UDP options */
//     ft_pckt_udp_opt_default(&opt.udp);

//     opt.udp.len = pckt.len - FT_IPHDR_LEN;
//     opt.udp.dport = resp.in.sin_port;

//     ft_pckt_udp_opt_set(&pckt, &opt.udp);

//   } else {
//     /* TCP options */
//     ft_pckt_tcp_opt_default(&opt.tcp);

//     opt.tcp.saddr = inet_addr(resp.addr);
//     opt.tcp.daddr = resp.in.sin_addr.s_addr;
//     opt.tcp.dport = resp.in.sin_port;
//     opt.tcp.seq = 1;

//     opt.tcp.flags = ft_nmap_exec_send_tcp_flags(resp.res_scan[iscan].key);

//     ft_pckt_tcp_opt_set(&pckt, &opt.tcp);
//   }

//   int i = ft_sendto(fd, pckt.data, pckt.len, &resp.in);

//   return (FT_EXOK);
// }

// int ft_nmap_exec_send(t_nmap_ctx ctx, t_nmap_opts opts, t_sockaddr_in in,
//                       int scan) {
//   int fd;
//   t_pckt pckt;
//   t_pckt_opt opt;

//   fd = ft_socket_raw();
//   ft_memset(&pckt, 0, sizeof(pckt));
//   ft_memset(&opt, 0, sizeof(opt));

//   pckt.len =
//       FT_IPHDR_LEN + (scan == FT_NMAP_SCAN_UDP ? FT_UDPHDR_LEN :
//       FT_TCPHDR_LEN);
//   if ((pckt.data = (t_uchar *)ft_memalloc(pckt.len)) == NULL)
//     return (FT_EXFAIL);

//   /* IP options */
//   ft_pckt_ip_opt_default(&opt.ip);

//   opt.ip.len = pckt.len;
//   opt.ip.proto = scan == FT_NMAP_SCAN_UDP ? IPPROTO_UDP : IPPROTO_TCP;
//   opt.ip.daddr = in.sin_addr.s_addr;

//   ft_pckt_ip_opt_set(&pckt, &opt.ip);

//   if (scan == FT_NMAP_SCAN_UDP) {
//     /* UDP options */
//     ft_pckt_udp_opt_default(&opt.udp);

//     opt.udp.len = pckt.len - FT_IPHDR_LEN;
//     opt.udp.dport = in.sin_port;

//     ft_pckt_udp_opt_set(&pckt, &opt.udp);

//   } else {
//     /* TCP options */
//     ft_pckt_tcp_opt_default(&opt.tcp);

//     opt.tcp.saddr = inet_addr(ctx.saddr);
//     opt.tcp.daddr = in.sin_addr.s_addr;
//     opt.tcp.dport = in.sin_port;
//     opt.tcp.seq = 1;
//     opt.tcp.flags = ft_nmap_exec_send_tcp_flags(scan);

//     ft_pckt_tcp_opt_set(&pckt, &opt.tcp);
//   }

//   int i = ft_sendto(fd, pckt.data, pckt.len, &in);

//   // i = connect(fd, (t_sockaddr *)&in, sizeof(t_sockaddr_in));
//   // printf("%d\n", i);

//   return (FT_EXOK);
// }
