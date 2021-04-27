/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_socket_packet.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/27 17:53:22 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

int   ft_traceroute_packet_set_header(t_trace *ctx)
{
  t_ip *ip = (t_ip *)ctx->to.pack.data;
  t_udp *udp = (t_udp *)(ctx->to.pack.data + sizeof(t_ip));

  ip->ip_ttl = ctx->opts.hops;
  udp->uh_dport = htons(ctx->opts.port + ctx->opts.hops + ctx->opts.probes); 

}

int   ft_traceroute_packet_init_header(t_trace *ctx)
{
  t_ip *ip;
  t_udp *udp;

  ip = &ctx->to.pack.ip;
  udp = &ctx->to.pack.udp;
  ip->ip_hl = 5; // Header len (5 * 4 Bytes)
  ip->ip_v = 4;
	// ip->ip_len = sizeof(t_tr_pack);
  ip->ip_len = ctx->opts.packetlen;
	ip->ip_id = getpid();
	ip->ip_p = IPPROTO_UDP;
  ip->ip_dst = ctx->to.saddrin.sin_addr;

	udp->uh_sport = htons(getpid());
	udp->uh_ulen = htons((u_short)(ip->ip_len - sizeof(t_ip)));  

  return (EXIT_SUCCESS);
}

int   ft_traceroute_packet_init_data(t_trace *ctx)
{
  char *datagram = "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~.";
  
  int datalen = ctx->opts.packetlen - sizeof(t_tr_pack);
  int datai = sizeof(t_tr_pack);

  // printf("%d, %d, %d\n", datai, datalen, ft_strlen(datagram));

  while (datalen > 0) {
    // if (datalen > 64)
    //   ft_memcpy(&ctx->sock.data[datai], datagram, 64);
    // else
    // printf("here\n");
      ft_memcpy(&ctx->to.pack.data[datai], datagram, datalen);
    datai += 64;
    datalen -= 64;
  }

  return (EXIT_SUCCESS);
}

int   ft_traceroute_packet_init(t_trace *ctx)
{
  t_sockaddr_in *to;

  to = &ctx->to.saddrin;

  to->sin_family = AF_INET;
  to->sin_addr.s_addr = inet_addr(ctx->to.ip); // Use inet_pton here

  // printf("packetlen: %d\n", ctx->opts.packetlen);

  if ((ctx->to.pack.data = ft_memalloc(ctx->opts.packetlen)) == NULL)
    return (EXIT_FAILURE);

  ft_traceroute_packet_init_header(ctx);

  ft_memcpy(ctx->to.pack.data, &ctx->to.pack, sizeof(t_ip) + sizeof(t_udp));

  ft_traceroute_packet_init_data(ctx);

  return (EXIT_SUCCESS);
}

int   ft_traceroute_packet_check(t_trace *ctx, char *buffer)
{
  t_ip    *ip;
  t_icmp  *icmp;
  t_udp   *udp;
  int hlen;
  char type;
  char code;

  ip = (t_ip *)buffer;
  hlen = ip->ip_hl << 2;
  icmp = (t_icmp *)(buffer + hlen);
	type = icmp->icmp_type;
  code = icmp->icmp_code;

  ctx->from.code = code;
  // if (code == ICMP_UNREACH)
  //   return (EXIT_FAILURE);
    // printf("DEST UNREACH\n");

  ip = &icmp->icmp_ip;
  hlen = ip->ip_hl << 2;

  udp = (t_udp *)((u_char *)ip + hlen);

  if (udp->uh_sport != htons(getpid()))
    return (EXIT_FAILURE);
  // if (ip->ip_id == getpid()) {
  //       printf("valid packet\n");
  // } else {
  //   printf("invalid packet");
  // }

  // if (udp->uh_sport == htons(getpid())) {
  //   printf("valid packet\n");
  // } else {
  //   printf("invalid packet");
  // }

  return (EXIT_SUCCESS);
}