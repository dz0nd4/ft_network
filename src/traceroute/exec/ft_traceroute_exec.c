/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/20 18:04:26 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static int 		ft_traceroute_exec_init(t_trace *ctx)
{
	t_addrinfo		hints;
	t_addrinfo		*result;
	t_addrinfo		*rp;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_UDP;
	// hints.ai_flags |= AI_CANONNAME;

	if (getaddrinfo(ctx->host.name, NULL, &hints, &result) != 0)
		return (EXIT_FAILURE);
	
	rp = result;
	if (rp->ai_next != NULL)
		fprintf(stderr, "target has multiple addresses\n");
	while (rp != NULL) {
		ctx->sock.udp = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (ctx->sock.udp != INVALID_SOCKET)
			break;
		rp = rp->ai_next;
	}

	if (rp == NULL)
		return (EXIT_FAILURE);

	ft_memcpy(&ctx->host.to, rp->ai_addr, sizeof(rp->ai_addr));
	ft_memcpy(ctx->host.ip, inet_ntoa(ctx->host.to.sin_addr), FT_ADDRSTRLEN);

	free(result);
  
	const int on = 1;

  if (setsockopt (ctx->sock.udp, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof(on)) < 0)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

static int 		ft_traceroute_exec_init_sockets(t_trace *ctx)
{
	if ((ctx->sock.icmp = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == INVALID_SOCKET)
		return (EXIT_FAILURE);

	ctx->to.sin_family = AF_INET;
	// ctx->to.sin_port = htons(FT_PORT_DEFAULT);
	ctx->to.sin_addr.s_addr = inet_addr(ctx->host.ip);
  
	t_ip *ip = &ctx->sock.udp_pack.ip;
  t_udp *udp = &ctx->sock.udp_pack.udp;

  ip->ip_hl = 5; // Header len (5 * 4 Bytes)
  ip->ip_v = 4; 
  ip->ip_tos = 0;
	ip->ip_off = 0;
	ip->ip_p = IPPROTO_UDP;
	ip->ip_len = sizeof(t_tr_pack);

	udp->uh_sport = htons(getpid());
	udp->uh_ulen = htons((u_short)(sizeof(t_tr_pack) - sizeof(t_ip)));
	udp->uh_sum = 0;

	return (EXIT_SUCCESS);
}

int 		ft_traceroute_exec(t_trace *ctx)
{
	int hops;
	int probes;
	int cc;

	hops = 1;
  if (ft_traceroute_exec_init(ctx) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (ft_traceroute_exec_init_sockets(ctx) == EXIT_FAILURE)
    return (EXIT_FAILURE);
	printf("traceroute to %s (%s), %d hops max, %d byte packets\n",
		ctx->host.name, ctx->host.ip, ctx->opts.hops_max, ctx->opts.packetlen);
	while (ctx->opts.hops <= ctx->opts.hops_max) {
		ctx->opts.probes = 0;
		while (ctx->opts.probes < ctx->opts.probes_max) {
			ft_traceroute_exec_send(ctx);
			cc = ft_traceroute_exec_receive(ctx);
			ft_traceroute_print(ctx, cc);

			ctx->opts.probes++;
		}
		
		printf("\n");

		if (ft_strequal(ctx->host.ip, inet_ntoa(ctx->from.sin_addr)))
			break;

		ctx->opts.hops++;
	}

	return (EXIT_SUCCESS);
}
