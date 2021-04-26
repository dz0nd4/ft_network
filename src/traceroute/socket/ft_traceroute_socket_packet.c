/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_socket_packet.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/26 11:19:25 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

int   ft_traceroute_packet_set_header(t_trace *ctx)
{
  t_ip *ip = (t_ip *)ctx->sock.data;
  t_udp *udp = (t_udp *)(ctx->sock.data + sizeof(t_ip));

  ip->ip_ttl = ctx->opts.hops;
  udp->uh_dport = htons(ctx->opts.port + ctx->opts.hops + ctx->opts.probes); 

}

int   ft_traceroute_packet_init_header(t_trace *ctx)
{
  t_ip *ip;
  t_udp *udp;

  ip = &ctx->sock.udp_pack.ip;
  udp = &ctx->sock.udp_pack.udp;
  ip->ip_hl = 5; // Header len (5 * 4 Bytes)
  ip->ip_v = 4;
	// ip->ip_len = sizeof(t_tr_pack);
  ip->ip_len = ctx->opts.packetlen;
	ip->ip_id = getpid();
	ip->ip_p = IPPROTO_UDP;
  ip->ip_dst = ctx->host.to.sin_addr;

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
      ft_memcpy(&ctx->sock.data[datai], datagram, datalen);
    datai += 64;
    datalen -= 64;
  }

  return (EXIT_SUCCESS);
}


int   ft_traceroute_packet_init(t_trace *ctx)
{
  t_sockaddr_in *to;

  to = &ctx->host.to;

  to->sin_family = AF_INET;
  to->sin_addr.s_addr = inet_addr(ctx->host.ip); // Use inet_pton here

  // printf("packetlen: %d\n", ctx->opts.packetlen);

  if ((ctx->sock.data = ft_memalloc(ctx->opts.packetlen)) == NULL)
    return (EXIT_FAILURE);

  ft_traceroute_packet_init_header(ctx);

  ft_memcpy(ctx->sock.data, &ctx->sock.udp_pack, sizeof(ctx->sock.udp_pack));

  ft_traceroute_packet_init_data(ctx);

  return (EXIT_SUCCESS);
}