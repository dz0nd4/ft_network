/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pckt_tcp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/12 09:40:25 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_sock.h"

char ft_sock_pckt_tcp(char *pckt, int pckt_len, t_sockaddr_in sin, int port) {
  t_iphdr *iphdr = (t_iphdr *)&pckt[0];
  t_tcphdr *tcp = (t_tcphdr *)&pckt[FT_IPHDR_LEN];
}

void ft_pckt_tcp_opt_default(t_pckt_tcp *opt) {
  ft_memset(opt, 0, sizeof(*opt));

  opt->sport = (43591 & FT_UINT16_MAX);
  opt->dport = (80 & FT_UINT16_MAX);
  opt->seq = 0x0;
  opt->ack_seq = 0x0;
  opt->doff = (5 & FT_UINT16_MAX);
  opt->window = (1024 & FT_UINT16_MAX);
}

void check_tcp_flag(t_tcphdr *tcp) {
  (tcp->syn == 1) ? printf("SYN ") : 0;
  (tcp->ack == 1) ? printf("ACK ") : 0;
  (tcp->fin == 1) ? printf("FIN ") : 0;
  (tcp->rst == 1) ? printf("RST ") : 0;
  (tcp->psh == 1) ? printf("PSH ") : 0;
  (tcp->urg == 1) ? printf("URG ") : 0;
  printf("\n");
}

void ft_pckt_tcp_opt_set(t_pckt *pckt, t_pckt_tcp *opt) {
  t_iphdr *ip = NULL;
  t_udphdr *udp = NULL;

  if (pckt == NULL || pckt->data == NULL || pckt->len == 0) return;

  // ft_memset(pckt->data, 0, pckt->len);

  ip = (t_iphdr *)&pckt->data[0];
  t_tcphdr *tcp = (t_tcphdr *)&pckt->data[FT_IPHDR_LEN];
  t_psh psh;

  // ft_pckt_ip_set(pckt, opt);

  tcp->doff = opt->doff;  // len
  tcp->source = htons(opt->sport);
  tcp->dest = htons(opt->dport);
  tcp->seq = htonl(opt->seq);

  tcp->ack_seq = opt->flags & FT_TCP_FLAG_ACK ? 1 : 0;

  // tcp->syn = 1;
  // tcp->ack = 0;  // Acknownledge

  tcp->urg = opt->flags & FT_TCP_FLAG_URG ? 1 : 0;  // Urgent flag
  tcp->ack = opt->flags & FT_TCP_FLAG_ACK ? 1 : 0;  // Acknownledge
  tcp->psh = opt->flags & FT_TCP_FLAG_PSH ? 1 : 0;  // Push data immediately
  tcp->rst = opt->flags & FT_TCP_FLAG_RST ? 1 : 0;  // RST flag
  tcp->syn = opt->flags & FT_TCP_FLAG_SYN ? 1 : 0;  // SYN flag
  tcp->fin = opt->flags & FT_TCP_FLAG_FIN ? 1 : 0;  // Terminates the connection

  tcp->window = htons(opt->window);
  tcp->urg_ptr = 0;

  psh.source_address = opt->saddr;
  psh.dest_address = opt->daddr;
  psh.placeholder = 0;
  psh.protocol = IPPROTO_TCP;
  psh.tcp_length = htons(sizeof(t_tcphdr));

  ft_memcpy(&psh.tcp, tcp, sizeof(t_tcphdr));

  tcp->check = 0;
  tcp->check = csum((unsigned short *)&psh, sizeof(struct pseudo_header));

  // check_tcp_flag(tcp);
}

// void ft_pckt_tcphdr(t_pckt *pckt, t_pckt_opt opt) {
//   t_tcphdr *tcp = NULL;
//   struct pseudo_header psh;

//   if (pckt == NULL || pckt->data == NULL || pckt->len == 0) return;

//   tcp = (t_tcphdr *)&pckt->data[FT_IPHDR_LEN];

//   // Populate tcp
//   tcp->source = htons(43591);  // 16 bit in nbp format of source port
//   tcp->dest = htons(80);       // 16 bit in nbp format of destination port
//   tcp->seq = 0x0;              // 32 bit sequence number, initially set to
//   zero tcp->ack_seq = 0x0;  // 32 bit ack seq number, depends if ACK is set
//   or not tcp->doff = 5;       // 4 bits: 5 x 32-bit words on tcp header
//   tcp->res1 = 0;       // 4 bits: Not used
//   // tcp->cwr = 0;              // Congestion control mechanism
//   // tcp->ece = 0;              // Congestion control mechanism
//   tcp->urg = 0;              // Urgent flag
//   tcp->ack = 0;              // Acknownledge
//   tcp->psh = 0;              // Push data immediately
//   tcp->rst = 0;              // RST flag
//   tcp->syn = 1;              // SYN flag
//   tcp->fin = 0;              // Terminates the connection
//   tcp->window = htons(155);  // 0xFFFF; //16 bit max number of databytes
//   tcp->check = 0;            // 16 bit check sum. Can't calculate at this
//   point tcp->urg_ptr = 0;  // 16 bit indicate the urgent data. Only if URG
//   flag is set

//   psh.source_address = inet_addr("10.0.2.15");
//   psh.dest_address = pckt->to.sin_addr.s_addr;
//   psh.placeholder = 0;
//   psh.protocol = IPPROTO_TCP;
//   psh.tcp_length = htons(sizeof(t_tcphdr));

//   ft_memcpy(&psh.tcp, tcp, sizeof(t_tcphdr));

//   tcp->check = csum((unsigned short *)&psh, sizeof(struct pseudo_header));
// }

// void ft_pckt_set_tcphdr(t_pckt *pckt, t_pckt_opt opt) {
//   t_iphdr *ip = NULL;
//   t_udphdr *udp = NULL;

//   if (pckt == NULL || pckt->data == NULL || pckt->len == 0) return;

//   // ft_memset(pckt->data, 0, pckt->len);

//   ip = (t_iphdr *)&pckt->data[0];
//   t_tcphdr *tcp = (t_tcphdr *)&pckt->data[FT_IPHDR_LEN];
//   struct pseudo_header psh;

//   // ft_pckt_ip_set(pckt, opt);

//   tcp->source = htons(43591);
//   tcp->check = 0;
//   tcp->dest = htons(pckt->to.sin_port);
//   tcp->seq = htonl(1);
//   tcp->doff = sizeof(t_tcphdr) / 4;  // len

//   tcp->ack_seq = 0;

//   tcp->syn = 1;
//   tcp->ack = 0;  // Acknownledge

//   tcp->window = htons(14600);
//   tcp->urg_ptr = 0;

//   psh.source_address = inet_addr("10.0.2.15");
//   psh.dest_address = pckt->to.sin_addr.s_addr;
//   psh.placeholder = 0;
//   psh.protocol = IPPROTO_TCP;
//   psh.tcp_length = htons(sizeof(t_tcphdr));

//   ft_memcpy(&psh.tcp, tcp, sizeof(t_tcphdr));

//   tcp->check = csum((unsigned short *)&psh, sizeof(struct pseudo_header));
// }
