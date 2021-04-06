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
#define __USE_BSD	/* use bsd'ish ip header */
#include <sys/socket.h>	/* these headers are for a Linux system, but */
#include <netinet/in.h>	/* the names on other systems are easy to guess.. */
#include <netinet/ip.h>
#define __FAVOR_BSD	/* use bsd'ish tcp header */
#include <netinet/tcp.h>
#include <unistd.h>
#include<errno.h>
#include<time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


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

int		ft_host_name_to_host_ipv4(char *host_name, char *host_ipv4)
{
	struct addrinfo		hints;
	struct addrinfo		*result;
	struct addrinfo		*rp;
	int sfd;
	struct sockaddr_in	*sa_in;
	char *str;

	// ft_memset(res, 0, sizeof(*res));
	// ft_memset(sa_in, 0, sizeof(*sa_in));

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	// hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	// hints.ai_flags = 0;
	// hints.ai_protocol = 0;          /* Any protocol */

	if (getaddrinfo(host_name, NULL, &hints, &result) != 0)
		ft_exit("getaddrinfo()");
	
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd != INVALID_SOCKET)
			break;
	}

	if (rp == NULL) {               /* No address succeeded */
			fprintf(stderr, "Could not connect\n");
			exit(EXIT_FAILURE);
	}

	sa_in = (struct sockaddr_in *)rp->ai_addr;

	// inet_ntop(res->ai_family, &(sa_in->sin_addr), ip_share, INET_ADDRSTRLEN);
	if ((str = inet_ntoa(sa_in->sin_addr)) == NULL) {
			perror("inet_ntoa");
			return (NULL);
	}

	ft_memcpy(host_ipv4, str, ft_strlen(str));

	return (EXIT_SUCCESS);
}

int				ft_traceroute_init(t_trace *ctx, const char *ipv4)
{
	ft_memset(ctx, 0, sizeof(*ctx));

	// char *ip = tr_get_ip_from_hostname(ipv4);


	ft_host_name_to_host_ipv4(ipv4, ctx->host_ipv4);

	printf("%s\n", ctx->host_ipv4);


	if (ft_ipv4_to_struct(&ctx->in_addr, ctx->host_ipv4) == EXIT_FAILURE) {
		return (EXIT_FAILURE);
	}
	ctx->target_ipv4 = ipv4;

	if ((ctx->sock_udp = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
		ft_exit("socket()");
	}
	// if ((ctx->sock_udp = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) == INVALID_SOCKET) {
	// 	return (EXIT_FAILURE);
	// }

	// if ((ctx->sock_icmp = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == INVALID_SOCKET) {
	// 	return (EXIT_FAILURE);
	// }

	ctx->addr_in_to.sin_family = AF_INET;
	ctx->addr_in_to.sin_addr.s_addr = inet_addr(ctx->target_ipv4);
	ctx->addr_in_to.sin_port = htons(33435);

	ctx->hops = 30;
	ctx->byte_packets = 60;
	// ctx->addr_in_to.porsin_port = 33435;

	return (EXIT_SUCCESS);
}
