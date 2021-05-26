/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_execute_init.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/27 00:55:01 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int   ft_traceroute_execute_send_init(t_tr_to *to)
{
  const int on = 1;

	// if (ft_sock_getaddrinfo(to->name, &to->addrinfo) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);

	to->sfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if (to->sfd == INVALID_SOCKET)
		{ printf("sfd\n") ; return (EXIT_FAILURE); }

	if (setsockopt(to->sfd, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof(on)) < 0)
   { printf ("opts\n"); return (EXIT_FAILURE); }

	ft_memcpy(&to->saddrin, to->addrinfo.ai_addr, sizeof(to->addrinfo.ai_addr));
	ft_memcpy(to->ip, inet_ntoa(to->saddrin.sin_addr), FT_ADDRSTRLEN);

  return (EXIT_SUCCESS);
}

int   ft_traceroute_execute_pack_init(t_trace *ctx, t_tr_to *to)
{
  char *datagram = "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~.";

  if ((ctx->to.pack.data = ft_memalloc(ctx->opts.packetlen)) == NULL)
    return (EXIT_FAILURE);

	to->hdr = (t_tr_pack_hdr *)to->pack.data;
  t_ip *ip = &to->hdr->ip;
  t_udp *udp = &to->hdr->udp;
  to->hdr->ip.ip_hl = 5; // Header len (5 * 4 Bytes)
  to->hdr->ip.ip_v = 4;
  to->hdr->ip.ip_len = ctx->opts.packetlen;
	to->hdr->ip.ip_id = getpid();
	to->hdr->ip.ip_p = IPPROTO_UDP;
  to->hdr->ip.ip_dst = ctx->to.saddrin.sin_addr;
  to->hdr->ip.ip_ttl = 0;

	to->hdr->udp.uh_sport = htons(getpid());
	to->hdr->udp.uh_ulen = htons((u_short)(to->hdr->ip.ip_len - sizeof(t_ip)));  
  to->hdr->udp.uh_dport = htons(ctx->opts.port); 

  int datai = sizeof(t_tr_pack_hdr);
  int datalen = ctx->opts.packetlen - datai;

  while (datalen > 0) {
		ft_memcpy(&to->pack.data[datai], datagram, datalen);
    datai += 64;
    datalen -= 64;
  }

  return (EXIT_SUCCESS);
}

int   ft_traceroute_execute_recv_init(t_tr_from *from)
{
  const int waittime = 5;

  ft_memset(from, 0, sizeof(t_tr_from));

  if ((from->sfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == INVALID_SOCKET)
		return (EXIT_FAILURE);
  from->saddrin_size = sizeof(from->saddrin);  
  from->wait.tv_sec = waittime;
  from->wait.tv_usec = 0;
  return (EXIT_SUCCESS);
}