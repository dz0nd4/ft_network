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

int			ft_ipv4_to_struct(struct in_addr *addr, char *ipv4)
{
	int domain;
	int	s;

	domain = AF_INET;
	s = inet_pton(domain, ipv4, addr);
	if (s <= 0) {
			if (s == 0)
					fprintf(stderr, "Not in presentation format\n");
			else
					perror("inet_pton");
			return(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char*			ft_struct_to_ipv4(struct in_addr *addr)
{
	char *ipv4;

	if ((ipv4 = inet_ntoa(*addr)) == NULL) {
			perror("inet_ntop");
			return (NULL);
	}
	return (ipv4);
}

int				ft_traceroute_init(t_trace *ctx, const char *ipv4)
{
	ft_memset(ctx, 0, sizeof(*ctx));

	if (ipv4 == NULL ||
			ft_ipv4_to_struct(&ctx->in_addr, (char *)ipv4) == EXIT_FAILURE) {
		return (EXIT_FAILURE);
	}
	ctx->target_ipv4 = ipv4;

	if ((ctx->sock_udp = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
		ft_exit("socket()");
	}
	// if ((ctx->sock_udp = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) == INVALID_SOCKET) {
	// 	return (EXIT_FAILURE);
	// }

	if ((ctx->sock_icmp = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == INVALID_SOCKET) {
		return (EXIT_FAILURE);
	}

	ctx->addr_in_to.sin_family = AF_INET;
	ctx->addr_in_to.sin_addr.s_addr = inet_addr(ctx->target_ipv4);
	ctx->addr_in_to.sin_port = htons(33435);

	ctx->hops = 30;
	ctx->byte_packets = 60;
	// ctx->addr_in_to.sin_port = 33435;

	return (EXIT_SUCCESS);
}
