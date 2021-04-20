/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/20 16:29:37 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int 	ft_tr_init_target_debug(t_trace *ctx)
{
	printf("|------------------|\n");
	printf("host: %s\n", ctx->host.name);
	printf("ip: %s\n", ctx->host.ip);
	printf("|------------------|\n");
	return (EXIT_SUCCESS);
}

int 	ft_tr_init_local(t_trace *ctx)
{
	t_addrinfo		hints;
	t_addrinfo		*result;
	t_addrinfo		*rp;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	// hints.ai_flags |= AI_CANONNAME;

	if (getaddrinfo("localhost", NULL, &hints, &result) != 0) {
		fprintf(stderr, "fail to getaddrinfo\n");
		return (EXIT_FAILURE);
	}
	
	rp = result;
	if (rp->ai_next != NULL)
		fprintf(stderr, "target has multiple addresses\n");
	while (rp != NULL) {
		ctx->sock.icmp = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (ctx->sock.icmp != INVALID_SOCKET)
			break;
		rp = rp->ai_next;
	}

	if (rp == NULL)
		return (EXIT_FAILURE);

	ft_memcpy(&ctx->host.from, rp->ai_addr, sizeof(rp->ai_addr));
	// ft_memcpy(ctx->host.ip, inet_ntoa(ctx->host.to.sin_addr), FT_ADDRSTRLEN);

	printf("%s\n", inet_ntoa(ctx->host.from.sin_addr));

	free(result);

	return (EXIT_SUCCESS);
}

int 	ft_tr_init_target(t_trace *ctx)
{
	t_addrinfo		hints;
	t_addrinfo		*result;
	t_addrinfo		*rp;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_UDP;
	hints.ai_flags |= AI_CANONNAME;

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

	return (EXIT_SUCCESS);
}

// int	ft_tr_init_sockets(t_trace *ctx)
// {
// 	t_addrinfo hints;
// 	t_addrinfo *res;
// 	t_addrinfo *rp;

// 	memset(&hints, 0, sizeof hints);
// 	hints.ai_family = AF_INET;
// 	hints.ai_socktype = SOCK_RAW;
// 	hints.ai_flags = AI_PASSIVE;
// 	hints.ai_protocol = IPPROTO_ICMP;
// 	hints.ai_canonname = NULL;
// 	hints.ai_addr = NULL;
// 	hints.ai_next = NULL;

// 	// if (getaddrinfo(NULL, NULL, &hints, &res) != 0) {
// 	// 	fprintf(stderr, "Could not getaddrinfo\n");
// 	// 	return (EXIT_FAILURE);
// 	// }
// 	// rp = res;
// 	// while (rp != NULL) {
// 	// 	ctx->sock.icmp = socket(rp->ai_family, rp->ai_socktype,
//   //   									rp->ai_protocol);
// 	// 	if (ctx->sock.icmp == INVALID_SOCKET)
// 	// 		continue;
		
// 	// 	if (bind(ctx->sock.icmp, rp->ai_addr, rp->ai_addrlen) == 0)
// 	// 		break;

// 	// 	close(ctx->sock.icmp);
// 	// }
// 	// if (rp == NULL) {
// 	// 	fprintf(stderr, "Could not bind\n");
// 	// 	return (EXIT_FAILURE);
// 	// }

// 	// if ((ctx->sock.udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
// 	// 	return (EXIT_FAILURE);

// 	if ((ctx->sock.udp = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) == INVALID_SOCKET)
// 		return (EXIT_FAILURE);

//   int on = 1;


//   if (setsockopt (ctx->sock.udp, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof(on)) < 0)
// 		ft_exit("IP_HDRINCL()");

// 	if ((ctx->sock.icmp = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == INVALID_SOCKET)
// 		return (EXIT_FAILURE);

// 	t_ip *ip = &ctx->sock.udp_pack.ip;
//   t_udp *udp = &ctx->sock.udp_pack.udp;

//   ip->ip_hl = 5; // Header len (5 * 4 Bytes)
//   ip->ip_v = 4; 

//   // ip->ip_dst = inet_addr(ctx->host.ip);
//   ip->ip_tos = 0;
// 	ip->ip_off = 0;
// 	ip->ip_p = IPPROTO_UDP;
// 	ip->ip_len = sizeof(t_tr_pack);
// 	// ip->ip_ttl = ctx->args.hops;

// 	udp->uh_sport = htons(getpid());
// 	// udp->uh_dport = htons(port + ctx->args.hops + ctx->args.probes);
// 	udp->uh_ulen = htons((u_short)(sizeof(t_tr_pack) - sizeof(t_ip)));
// 	udp->uh_sum = 0;

// 	return (EXIT_SUCCESS);
// }

int		ft_tr_init_opts(t_trace *ctx)
{
	t_tr_opt	*opt;

	opt = &ctx->opts;
	opt->hops = FT_DEFAULT_HOPS;
	opt->hops_max = FT_DEFAULT_HOPS_MAX;
	opt->probes_max = FT_DEFAULT_PROBES_MAX;
	opt->port = FT_DEFAULT_PORT;
	opt->packetlen = sizeof(t_ip) + 40;
	return (EXIT_SUCCESS);
}

// int				ft_traceroute_init(t_trace *ctx, const char *ipv4)
// {
// 	ctx->host.name = ipv4;

// 	// if (ft_host_name_to_host_ipv4(ctx->host_name, ctx->host_ipv4) == EXIT_FAILURE)
// 	// 	return (EXIT_FAILURE);
// 	if(geteuid() != EXIT_SUCCESS)
// 		return (ft_traceroute_perm());

// 	if (ft_tr_init_target(ctx) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);

// 	if (ft_tr_init_sockets(ctx) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);

// 	// ft_tr_init_args(ctx);

// 	return (EXIT_SUCCESS);
// }

int	ft_traceroute_init_exec(t_trace *ctx)
{

}

// int	ft_traceroute_init(t_trace *ctx)
// {
// 	t_tr_opt	*opt;

// 	opt = &ctx->opts;

// 	if (geteuid() != 0) {
// 		fprintf(stderr, "/!\\ You don't have root privileges /!\\\n");
// 		// return (EXIT_FAILURE);
// 	}

// 	opt->hops = FT_DEFAULT_HOPS;
// 	opt->hops_max = FT_DEFAULT_HOPS_MAX;
// 	opt->probes_max = FT_DEFAULT_PROBES_MAX;
// 	opt->port = FT_DEFAULT_PORT;
// 	opt->packetlen = sizeof(t_ip) + 40;

// 	return (EXIT_SUCCESS);
// }

// int	ft_traceroute_init_2(t_trace *ctx)
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