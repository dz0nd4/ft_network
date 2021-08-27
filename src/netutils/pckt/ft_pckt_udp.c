/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pckt_udp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/12 09:33:24 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_sock.h"

void ft_pckt_udp_opt_default(t_pckt_udp *opt) {
  ft_memset(opt, 0, sizeof(*opt));

  opt->sport = (getpid() & FT_UINT16_MAX);
}

void ft_pckt_udp_opt_set(t_pckt *pckt, t_pckt_udp *opts) {
  t_udphdr *udp = NULL;

  if (pckt == NULL || pckt->data == NULL || pckt->len == 0 || opts == NULL)
    return;

  udp = (t_udphdr *)&pckt->data[FT_IPHDR_LEN];

  udp->uh_ulen = htons(opts->len);
  udp->uh_dport = htons(opts->dport);
  udp->uh_sport = htons(opts->sport);

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