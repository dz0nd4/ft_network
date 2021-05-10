/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_execute.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/10 15:26:00 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

// static int 	ft_traceroute_execute_send_init(t_trace *ctx, t_tr_to *to)
// {
// 	const int on = 1;
//   t_addrinfo result, *rp;


// 	if (ft_socket_getaddrinfo(to->name, &result) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);

// 	rp = &result;

// 	to->sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
// 	if (to->sfd == INVALID_SOCKET)
// 		return (EXIT_FAILURE);
	
// 	ft_memcpy(&to->saddrin, rp->ai_addr, sizeof(rp->ai_addr));
// 	ft_memcpy(to->ip, inet_ntoa(to->saddrin.sin_addr), FT_ADDRSTRLEN);

//   if (setsockopt(to->sfd, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof(on)) < 0)
// 		return (EXIT_FAILURE);
	
//   if ((to->pack.data = ft_memalloc(ctx->opts.packetlen)) == NULL)
//     return (EXIT_FAILURE);
	
// 	to->hdr = (t_tr_pack_hdr *)to->pack.data;
// 	t_tr_pack_hdr *hdr = to->hdr;

// }

static int 	ft_traceroute_execute_init(t_trace *ctx)
{
	if (ft_traceroute_execute_send_init(&ctx->to) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (ft_traceroute_execute_pack_init(ctx, &ctx->to) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (ft_traceroute_execute_recv_init(&ctx->from) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	
	return (EXIT_SUCCESS);
}

int 		ft_traceroute_execute(t_trace *ctx)
{
	int cc;
  char buffer[BUF_SIZE];
  t_tr_from *from;
  fd_set    fds;

			FD_ZERO(&fds);
  from = &ctx->from;
	ctx->opts.probes = -1;
	if (ft_traceroute_execute_init(ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	printf("traceroute to %s (%s), %d hops max, %d byte packets\n",
		ctx->to.name, ctx->to.ip, ctx->opts.hops_max, ctx->opts.packetlen);
	while (ft_traceroute_execute_send(ctx, &ctx->opts, &ctx->to)) {
			FD_ZERO(&fds);
			FD_SET(from->sfd, &fds);
			if (select(from->sfd + 1, &fds, (fd_set *)0, (fd_set *)0, &from->wait) > 0)
				if (ft_traceroute_execute_recv(ctx, &ctx->from.buffer, from) == EXIT_SUCCESS)
					break ;
	}

	return (EXIT_SUCCESS);
}

// int 		ft_traceroute_execute(t_trace *ctx)
// {
// 	int cc;
//   char buffer[BUF_SIZE];
//   t_tr_from *from;
//   fd_set    fds;

// 			FD_ZERO(&fds);
//   from = &ctx->from;
// 	// FD_ZERO(&fds);
// 	// FD_SET(from->sfd, &fds);
// 	ctx->opts.probes = -1;
// 	if (ft_traceroute_execute_init(ctx) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	// ft_traceroute_display_infos_host(ctx);
// 	printf("traceroute to %s (%s), %d hops max, %d byte packets\n",
// 		ctx->to.name, ctx->to.ip, ctx->opts.hops_max, ctx->opts.packetlen);
// 	while (ft_traceroute_execute_send(ctx, &ctx->opts, &ctx->to)) {
// 		// ctx->opts.probes = 0;
// 		// while (ctx->opts.probes < ctx->opts.probes_max) {
// 		// 	ft_traceroute_socket_send(ctx);
// 			FD_ZERO(&fds);
// 			FD_SET(from->sfd, &fds);
// 			if (select(from->sfd + 1, &fds, (fd_set *)0, (fd_set *)0, &from->wait) > 0)
// 				if (ft_traceroute_execute_receive(ctx, &ctx->from.buffer, from) == EXIT_SUCCESS)
// 					break ;
// 			// if (ft_traceroute_packet_check(ctx, &ctx->from.buffer) == EXIT_SUCCESS)
// 			// 	ft_traceroute_print(ctx, cc);

// 			// ctx->opts.probes++;
// 		// }
		
// 		// printf("\n");
// 		// if (ctx->from.code == ICMP_UNREACH)
// 		// 	break;
// 		// if (ft_strequal(ctx->to.ip, inet_ntoa(ctx->from.saddrin.sin_addr)))
// 		// 	break;

// 		// ctx->opts.hops++;
// 	}

// 	return (EXIT_SUCCESS);
// }
