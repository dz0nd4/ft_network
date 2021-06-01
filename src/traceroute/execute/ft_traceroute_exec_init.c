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

int   ft_traceroute_exec_send_init(t_trace *ctx, t_tr_to *to)
{
  const int on = 1;

	// if (ft_sock_getaddrinfo(to->name, &to->addrinfo) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);

	to->sfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if (to->sfd == INVALID_SOCKET)
		{ printf("sfd\n") ; return (EXIT_FAILURE); }

	if (setsockopt(to->sfd, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof(on)) < 0)
   { printf ("opts\n"); return (EXIT_FAILURE); }

	ft_memcpy(&to->saddrin, ctx->to.addrinfo.ai_addr, sizeof(ctx->to.addrinfo.ai_addr));
	ft_memcpy(to->ip, inet_ntoa(to->saddrin.sin_addr), FT_ADDRSTRLEN);
  to->name = ctx->to.name;


  return (EXIT_SUCCESS);
}

int   ft_traceroute_exec_pack_init(t_trace *ctx, t_tr_to *to)
{
  const char *datagram = "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~.";
  t_ip  *ip;
  t_udp *udp;

  if ((to->data = ft_memalloc(ctx->opts.packetlen)) == NULL)
    return (EXIT_FAILURE);

  ip = (t_ip *)to->data;
  udp = (t_udp *)&to->data[FT_IPHDR_LEN];

  ip->ip_hl = 5; // Header len (5 * 4 Bytes)
  ip->ip_v = 4;
  ip->ip_len = ctx->opts.packetlen;
	ip->ip_id = getpid();
	ip->ip_p = IPPROTO_UDP;
  ip->ip_dst = to->saddrin.sin_addr;
  ip->ip_ttl = 0;

	udp->uh_sport = htons(getpid());
	udp->uh_ulen = htons((u_short)(ip->ip_len - sizeof(t_ip)));  
  udp->uh_dport = htons(ctx->opts.port); 

  int datai = FT_UDPHDR_LEN;
  int datalen = ctx->opts.packetlen - datai;

  while (datalen > 0) {
		ft_memcpy(&to->data[datai], datagram, datalen);
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
  // ft_setsockopt_rcvtimeo(&from->sfd, 1, 1);
  from->saddrin_size = sizeof(from->saddrin);
  from->wait.tv_sec = waittime;
  from->wait.tv_usec = 0;
  return (EXIT_SUCCESS);
}