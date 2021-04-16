/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/06 13:13:35 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

// int			ft_ipv4_to_struct(struct in_addr *addr, char *ipv4)
// {
// 	int domain;
// 	int	s;

// 	domain = AF_INET;
// 	s = inet_pton(domain, ipv4, addr);
// 	if (s <= 0) {
// 			if (s == 0)
// 					fprintf(stderr, "Not in presentation format\n");
// 			else
// 					perror("inet_pton");
// 			return(EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }

// char*			ft_struct_to_ipv4(struct in_addr *addr)
// {
// 	char *ipv4;

// 	if ((ipv4 = inet_ntoa(*addr)) == NULL) {
// 			perror("inet_ntop");
// 			return (NULL);
// 	}
// 	return (ipv4);
// }

static int 	ft_tr_init_target(t_trace *ctx)
{
	t_addrinfo		hints;
	t_addrinfo		*result;
	t_addrinfo		*rp;
	int sfd;
	struct sockaddr_in	*sa_in;
	char *str;

	// ft_memset(res, 0, sizeof(*res));
	// ft_memset(sa_in, 0, sizeof(*sa_in));

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = 0;
	hints.ai_protocol = 0;          /* Any protocol */

	if (getaddrinfo(ctx->host.name, NULL, &hints, &result) != 0)
		return (EXIT_FAILURE);// ft_exit("getaddrinfo()");
	
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		// printf("%s\n", rp->ai_canonname);
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd != INVALID_SOCKET)
			break;
	}

	if (rp == NULL)
		return (EXIT_FAILURE);// exit(EXIT_FAILURE);

	sa_in = (struct sockaddr_in *)rp->ai_addr;

	if ((str = inet_ntoa(sa_in->sin_addr)) == NULL)
		return (EXIT_FAILURE);

	ft_memcpy(ctx->host.ip, str, ft_strlen(str));
	// ctx->to.sin_family = AF_INET;
	// ctx->to.sin_port = htons(FT_PORT_DEFAULT);
	// ctx->to.sin_addr.s_addr = inet_addr(ctx->host_ipv4);

	// if (ctx->to.sin_addr.s_addr == -1)
	// 	return (EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}

static int	ft_tr_init_sockets(t_trace *ctx)
{
	t_addrinfo hints;
	t_addrinfo *res;
	t_addrinfo *rp;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = IPPROTO_ICMP;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	// if (getaddrinfo(NULL, NULL, &hints, &res) != 0) {
	// 	fprintf(stderr, "Could not getaddrinfo\n");
	// 	return (EXIT_FAILURE);
	// }
	// rp = res;
	// while (rp != NULL) {
	// 	ctx->sock.icmp = socket(rp->ai_family, rp->ai_socktype,
  //   									rp->ai_protocol);
	// 	if (ctx->sock.icmp == INVALID_SOCKET)
	// 		continue;
		
	// 	if (bind(ctx->sock.icmp, rp->ai_addr, rp->ai_addrlen) == 0)
	// 		break;

	// 	close(ctx->sock.icmp);
	// }
	// if (rp == NULL) {
	// 	fprintf(stderr, "Could not bind\n");
	// 	return (EXIT_FAILURE);
	// }

	if ((ctx->sock.udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
		return (EXIT_FAILURE);

	if ((ctx->sock.icmp = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == INVALID_SOCKET)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

static int	ft_tr_init_args(t_trace *ctx)
{
	ctx->args.hops = 1;
	ctx->args.hops_max = 30;
	ctx->args.probes_max = 3;
	ctx->args.byte_packets = 60;
	return (EXIT_SUCCESS);
}

int				ft_traceroute_init(t_trace *ctx, const char *ipv4)
{
	ctx->host.name = ipv4;

	// if (ft_host_name_to_host_ipv4(ctx->host_name, ctx->host_ipv4) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	// if(geteuid() != EXIT_SUCCESS)
	// 	return (ft_traceroute_perm());

	// if (ft_tr_init_target(ctx) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);

	// if (ft_tr_init_sockets(ctx) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);

	ft_tr_init_args(ctx);

	return (EXIT_SUCCESS);
}
