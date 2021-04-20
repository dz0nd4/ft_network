/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/20 17:58:09 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

// static int	ft_traceroute_init_2(t_trace *ctx)
// {
// 	const int on = 1;
// 	t_ip *ip;
// 	t_udp *udp;
// 	t_tr_opt	*opt;

// 	if (geteuid() != 0) {
// 		fprintf(stderr, "/!\\ You don't have root privileges /!\\\n");
// 		// return (EXIT_FAILURE);
// 	}

// 	if ((ctx->sock.udp = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) == INVALID_SOCKET)
// 		return (EXIT_FAILURE);
// 	if ((ctx->sock.icmp = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == INVALID_SOCKET)
// 		return (EXIT_FAILURE);
//   if (setsockopt (ctx->sock.udp, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof(on)) < 0)
// 		return (EXIT_FAILURE);

// 	ip = &ctx->sock.udp_pack.ip;
// 	ip->ip_hl = 5; // Header len (5 * 4 Bytes)
//   ip->ip_v = 4;
// 	ip->ip_p = IPPROTO_UDP;
// 	ip->ip_len = sizeof(t_tr_pack);

//   udp = &ctx->sock.udp_pack.udp;
// 	udp->uh_sport = htons(getpid());
// 	udp->uh_ulen = htons((u_short)(sizeof(t_tr_pack) - sizeof(t_ip)));
// 	udp->uh_sum = 0;

// 	opt = &ctx->opts;
// 	opt->hops = FT_DEFAULT_HOPS;
// 	opt->hops_max = FT_DEFAULT_HOPS_MAX;
// 	opt->probes_max = FT_DEFAULT_PROBES_MAX;
// 	opt->port = FT_DEFAULT_PORT;
// 	opt->packetlen = sizeof(t_ip) + 40;

// 	return (EXIT_SUCCESS);
// }
static int	ft_traceroute_init(t_trace *ctx, int argc, const char *argv[])
{
	t_tr_opt	*opt;

	if (geteuid() != FT_TR_ROOT) {
		fprintf(stderr, "/!\\ You don't have root privileges /!\\\n");
		// return (EXIT_FAILURE);
	}

	if (argc < 2)
		return (ft_traceroute_usage((char *)argv[0]));

	ctx->argi = 1;

	opt = &ctx->opts;
	opt->hops = FT_DEFAULT_HOPS;
	opt->hops_max = FT_DEFAULT_HOPS_MAX;
	opt->probes_max = FT_DEFAULT_PROBES_MAX;
	opt->port = FT_DEFAULT_PORT;
	opt->packetlen = sizeof(t_ip) + 40;

	return (EXIT_SUCCESS);
}

int			ft_traceroute(int argc, const char *argv[])
{
	t_trace	ctx;

	ft_memset(&ctx, 0, sizeof(ctx));

	if (ft_traceroute_init(&ctx, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (ft_traceroute_parse(&ctx, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// ft_traceroute_parse_debug(&ctx);

	if (ft_traceroute_exec(&ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	// if (ft_tr_init_target(&ctx) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	// ft_tr_init_target_debug(&ctx);
	
	// if (ft_tr_init_local(&ctx) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);

	// if (argv[1] == NULL || ft_strequal(argv[1], "-h"))
	// 	return (ft_traceroute_help((char *)argv[0]));

	// if (ft_traceroute_init(&ctx, argv[1]) == EXIT_FAILURE)
	// 	ft_exit("traceroute_init()");
	// ft_tr_init_sockets(&ctx);


	// ft_traceroute_exec(&ctx);

	// close(ctx.sock.udp);
	// close(ctx.sock.icmp);

	return (EXIT_SUCCESS);
}

	// if (BYTE_ORDER == LITTLE_ENDIAN)
	// 	printf("little\n");
	// else if (BYTE_ORDER == BIG_ENDIAN)
	// 	printf("big\n");