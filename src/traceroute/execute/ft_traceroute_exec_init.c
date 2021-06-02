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

int 	ft_traceroute_exec_init_to(t_trace *tr, t_tr_sock *to)
{
	const int on = 1;
	const char *datagram = "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~.";
	t_ip 			*ip;
	t_udp			*udp;
	t_addrinfo	addrinfo;

	ft_memset(&addrinfo, 0, sizeof(0));

	addrinfo.ai_family = AF_INET;
	addrinfo.ai_socktype = SOCK_DGRAM;
	addrinfo.ai_protocol = IPPROTO_UDP;

	if (ft_getaddrinfo(tr->opts.host, &addrinfo) == FT_EXFAIL) {
		fprintf(stderr, "Unkown host\n");
		return (FT_EXFAIL);
		// return (ft_tr_err_arg_host(args));
	}

	if ((to->fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) == INVALID_SOCKET)
		return (FT_EXFAIL);
	if (setsockopt(to->fd, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof(on)) < 0)
   return (EXIT_FAILURE);

	ft_memcpy(&to->saddrin, addrinfo.ai_addr, sizeof(addrinfo.ai_addr));

	to->datalen = tr->opts.packetlen;
  if ((to->data = ft_memalloc(tr->opts.packetlen)) == NULL)
    return (EXIT_FAILURE);

  ip = (t_ip *)to->data;
  udp = (t_udp *)&to->data[FT_IPHDR_LEN];

  ip->ip_hl = 5; // Header len (5 * 4 Bytes)
  ip->ip_v = 4;
  ip->ip_len = tr->opts.packetlen;
	ip->ip_id = getpid();
	ip->ip_p = IPPROTO_UDP;
  ip->ip_dst = to->saddrin.sin_addr;
  ip->ip_ttl = 0;

	udp->uh_sport = htons(getpid());
	udp->uh_ulen = htons((u_short)(ip->ip_len - sizeof(t_ip)));  
  udp->uh_dport = htons(tr->opts.port);

	int i = FT_UDPHDR_LEN;
	int idata = 0;

	while (i < to->datalen) {
		to->data[i] = datagram[idata];
		i += 1;
		if (++idata == ft_strlen(datagram))
			idata = 0;
	}

	return (FT_EXOK);
}

int 	ft_traceroute_exec_init_from(t_tr_opts *opts, t_tr_sock *from)
{
  const int waittime = 5;

  // ft_memset(from, 0, sizeof(t_tr_from));

  if ((from->fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == INVALID_SOCKET)
		return (FT_EXFAIL);
  // ft_setsockopt_rcvtimeo(&from->sfd, 1, 1);

	from->datalen = opts->packetlen;
  if ((from->data = ft_memalloc(opts->packetlen)) == NULL)
    return (FT_EXFAIL);

  // from->saddrin_size = sizeof(from->saddrin);
  from->tv.tv_sec = waittime;
  from->tv.tv_usec = 0;

	return (FT_EXOK);
}
