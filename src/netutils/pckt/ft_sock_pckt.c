/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sock_pckt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/07/29 17:29:31 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_sock.h"

/*
 Checksums - IP and TCP
 */
unsigned short csum(unsigned short *ptr, int nbytes) {
  register long sum;
  unsigned short oddbyte;
  register short answer;

  sum = 0;
  while (nbytes > 1) {
    sum += *ptr++;
    nbytes -= 2;
  }
  if (nbytes == 1) {
    oddbyte = 0;
    *((u_char *)&oddbyte) = *(u_char *)ptr;
    sum += oddbyte;
  }

  sum = (sum >> 16) + (sum & 0xffff);
  sum = sum + (sum >> 16);
  answer = (short)~sum;

  return (answer);
}

t_uchar *ft_pckt_random_data(t_uchar *data, t_uint16 len) {
  t_uint16 i = 0;

  while (i < len) {
    data[i++] = i + '0';
  }
  data[i] = 0;

  return (data);
}

int ft_pckt_ip_set(t_pckt *pckt, t_pckt_opt opt) {
  t_iphdr *ip = NULL;

  if (pckt == NULL || pckt->data == NULL || pckt->len == 0) return (FT_EXFAIL);

  ip = (t_iphdr *)&pckt->data[0];

  ip->ihl = 5;  // Header len (5 * 4 Bytes)
  ip->version = 4;
  ip->tot_len = pckt->len;
  ip->id = pckt->id;
  ip->protocol = opt.proto;
  ip->daddr = pckt->to.sin_addr.s_addr;
  ip->ttl = opt.ttl;

  return (FT_EXOK);
}

void ft_pckt_set_time(t_uchar *data) {
  t_timeval tv;

  ft_memset(&tv, 0, sizeof(tv));
  ft_gettimeofday(&tv);
  ft_memcpy(data, &tv, sizeof(tv));
}

void ft_pckt_set_icmp(t_pckt *pckt, t_pckt_opt opt) {
  t_iphdr *ip = NULL;
  t_icmphdr *icmp = NULL;
  t_timeval *tv;

  if (pckt == NULL || pckt->data == NULL || pckt->len == 0) return;

  ft_memset(pckt->data, 0, pckt->len);

  ip = (t_iphdr *)&pckt->data[0];
  icmp = (t_icmphdr *)&pckt->data[FT_IPHDR_LEN];
  tv = (t_timeval *)&pckt->data[FT_PING_HDR];

  ft_pckt_ip_set(pckt, opt);

  icmp->type = ICMP_ECHO;
  icmp->un.echo.id = pckt->id;
  icmp->un.echo.sequence = opt.seq;
  icmp->checksum = 0;

  if ((pckt->len - FT_PING_HDR) >= FT_TIMEVAL_LEN) {
    ft_pckt_set_time(&pckt->data[FT_PING_HDR]);
    // ft_memset(&pckt->data[FT_PING_HDR], 0, sizeof(t_timeval));
    // ft_gettimeofday(tv);
  }

  icmp->checksum =
      ft_checksum(&pckt->data[FT_IPHDR_LEN], (pckt->len - FT_IPHDR_LEN));

  // printf("id: %d  \n", icmp->un.echo.id);
  // printf("seq: %d  \n", icmp->un.echo.sequence);
  // printf("ck: %d  \n", icmp->checksum);
}

void ft_pckt_set_udphdr(t_pckt *pckt, t_pckt_opt opt) {
  t_iphdr *ip = NULL;
  t_udphdr *udp = NULL;
  t_timeval *tv;

  if (pckt == NULL || pckt->data == NULL || pckt->len == 0) return;

  ft_memset(pckt->data, 0, pckt->len);

  ip = (t_iphdr *)&pckt->data[0];
  udp = (t_udphdr *)&pckt->data[FT_IPHDR_LEN];
  tv = (t_timeval *)&pckt->data[FT_TRACE_HDR];

  ft_pckt_ip_set(pckt, opt);

  udp->uh_sport = htons(getpid());
  udp->uh_ulen = htons((uint16_t)(ip->tot_len - FT_IPHDR_LEN));
  udp->uh_dport = htons(opt.port);

  if ((pckt->len - FT_TRACE_HDR) >= FT_TIMEVAL_LEN) {
    ft_pckt_set_time(&pckt->data[FT_TRACE_HDR]);
  }
}

void ft_sock_pckt_udphdr(char *pckt, int pckt_len, t_sockaddr_in saddrin,
                         int port) {
  const char *datagram =
      "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~.";
  t_iphdr *iphdr;
  t_udphdr *udp;
  int i;
  int idata;

  iphdr = (t_iphdr *)pckt;
  udp = (t_udphdr *)&pckt[FT_IPHDR_LEN];

  iphdr->ihl = 5;  // Header len (5 * 4 Bytes)
  iphdr->version = 4;
  iphdr->tot_len = pckt_len;
  iphdr->id = getpid();
  iphdr->protocol = IPPROTO_UDP;
  iphdr->daddr = saddrin.sin_addr.s_addr;
  iphdr->ttl = 0;

  udp->uh_sport = htons(getpid());
  udp->uh_ulen = htons((uint16_t)(iphdr->tot_len - FT_IPHDR_LEN));
  udp->uh_dport = htons(port);

  i = FT_TRACE_HDR;
  idata = 0;

  while (i < pckt_len) {
    pckt[i++] = datagram[idata];
    if (++idata == ft_strlen(datagram)) idata = 0;
  }
}

char ft_sock_pckt_tcp(char *pckt, int pckt_len, t_sockaddr_in sin, int port) {
  t_iphdr *iphdr = (t_iphdr *)&pckt[0];
  t_tcphdr *tcphdr = (t_tcphdr *)&pckt[FT_IPHDR_LEN];
}

void ft_pckt_tcphdr(t_pckt *pckt, t_pckt_opt opt) {
  t_tcphdr *tcphdr = NULL;
  struct pseudo_header psh;

  if (pckt == NULL || pckt->data == NULL || pckt->len == 0) return;

  tcphdr = (t_tcphdr *)&pckt->data[FT_IPHDR_LEN];

  // Populate tcphdr
  tcphdr->source = htons(43591);  // 16 bit in nbp format of source port
  tcphdr->dest = htons(80);       // 16 bit in nbp format of destination port
  tcphdr->seq = 0x0;  // 32 bit sequence number, initially set to zero
  tcphdr->ack_seq =
      0x0;  // 32 bit ack sequence number, depends whether ACK is set or not
  tcphdr->doff = 5;  // 4 bits: 5 x 32-bit words on tcp header
  tcphdr->res1 = 0;  // 4 bits: Not used
  // tcphdr->cwr = 0;              // Congestion control mechanism
  // tcphdr->ece = 0;              // Congestion control mechanism
  tcphdr->urg = 0;              // Urgent flag
  tcphdr->ack = 0;              // Acknownledge
  tcphdr->psh = 0;              // Push data immediately
  tcphdr->rst = 0;              // RST flag
  tcphdr->syn = 1;              // SYN flag
  tcphdr->fin = 0;              // Terminates the connection
  tcphdr->window = htons(155);  // 0xFFFF; //16 bit max number of databytes
  tcphdr->check = 0;  // 16 bit check sum. Can't calculate at this point
  tcphdr->urg_ptr =
      0;  // 16 bit indicate the urgent data. Only if URG flag is set

  psh.source_address = inet_addr("10.0.2.15");
  psh.dest_address = pckt->to.sin_addr.s_addr;
  psh.placeholder = 0;
  psh.protocol = IPPROTO_TCP;
  psh.tcp_length = htons(sizeof(struct tcphdr));

  ft_memcpy(&psh.tcp, tcphdr, sizeof(struct tcphdr));

  tcphdr->check = csum((unsigned short *)&psh, sizeof(struct pseudo_header));
}

void ft_pckt_set_tcphdr(t_pckt *pckt, t_pckt_opt opt) {
  t_iphdr *ip = NULL;
  t_udphdr *udp = NULL;

  if (pckt == NULL || pckt->data == NULL || pckt->len == 0) return;

  ft_memset(pckt->data, 0, pckt->len);

  ip = (t_iphdr *)&pckt->data[0];
  t_tcphdr *tcphdr = (t_tcphdr *)&pckt->data[FT_IPHDR_LEN];
  struct pseudo_header psh;

  ft_pckt_ip_set(pckt, opt);

  tcphdr->source = htons(43591);
  tcphdr->check = 0;
  tcphdr->dest = htons(80);
  tcphdr->seq = htonl(1);
  tcphdr->doff = sizeof(struct tcphdr) / 4;  // len

  tcphdr->ack_seq = 0;

  tcphdr->syn = 1;
  tcphdr->ack = 0;  // Acknownledge

  tcphdr->window = htons(14600);
  tcphdr->urg_ptr = 0;

  psh.source_address = inet_addr("10.0.2.15");
  psh.dest_address = pckt->to.sin_addr.s_addr;
  psh.placeholder = 0;
  psh.protocol = IPPROTO_TCP;
  psh.tcp_length = htons(sizeof(struct tcphdr));

  ft_memcpy(&psh.tcp, tcphdr, sizeof(struct tcphdr));

  tcphdr->check = csum((unsigned short *)&psh, sizeof(struct pseudo_header));
}