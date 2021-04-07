/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/06 13:17:47 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static int			ft_traceroute_help()
{
	printf("Usage:\n");
	printf(" <sudo> ft_traceroute host\n");
	return (EXIT_FAILURE);
}

static int			ft_traceroute_perm()
{
	printf("/!\\ You don't have root privileges /!\\\n");
	return (ft_traceroute_help());
}

void ft_exit(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void ft_traceroute_exit(char *s)
{
	fprintf(stderr, "%s\n", s);
	exit(EXIT_FAILURE);
}

// int			ft_traceroute_wait(t_trace *ctx)
// {
// 	fd_set 	rdfs;
// 	int			ready_for_reading = 0;
// 	SOCKADDR_IN to = { 0 };
// 	SOCKADDR_IN from = { 0 };
// 	char buffer[BUF_SIZE];

// 	FD_ZERO(&rdfs);
// 	FD_SET(ctx->sock_icmp, &rdfs);

// 	ready_for_reading = select(ctx->sock_icmp + 1, &rdfs, NULL, NULL, NULL);

// 	if (ready_for_reading) {
// 		printf("ready !!\n");
// 	} else {
// 		printf("error !!\n");
// 	}

// 	if(FD_ISSET(ctx->sock_icmp, &rdfs))
// 		{
// 			int n = read_server(ctx->sock_icmp, &to, buffer);
// 			/* server down */
// 			if(n == 0) {
// 				ft_exit("read_server()");
// 			} else {
// 				printf("receiving msg from server");
// 			}
// 			puts(buffer);
// 		}
// }

int 		ft_traceroute_exec(t_trace *ctx)
{
	SOCKADDR_IN to = { 0 };
	SOCKADDR_IN from = { 0 };
	char buffer[BUF_SIZE];
	fd_set rdfs;
int             ready_for_reading = 0;

	int port = 33435;

	// to.sin_addr.s_addr = inet_addr(ctx->target_ipv4);
	// to.sin_port = htons(++port);
	// to.sin_family = AF_INET;

	// ft_traceroute_wait(ctx);

	printf("traceroute to %s (%s), %d hops max, %d byte packets\n", ctx->host_name, ctx->host_ipv4, ctx->hops, ctx->byte_packets);

	for (int i = 1; i < ctx->hops; i++) {

		ft_traceroute_send(ctx, port + i, i);
		ft_traceroute_receive(ctx, i);
		// ctx->addr_in_to.sin_port = htons(port);
		// // to.sin_addr.s_addr = inet_addr(ctx->target_ipv4);
		// // to.sin_port = htons(++port);
		// // to.sin_family = AF_INET;

		// int ttl = i;
		// if (setsockopt(ctx->sock_udp, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
    //   printf ("Warning: Cannot set TTL!\n");

		// write_server(ctx->sock_udp, &ctx->addr_in_to, buffer);
		// read_server(ctx->sock_icmp, &from, buffer);
	}

	return (EXIT_SUCCESS);
}



int			ft_traceroute(int argc, const char *argv[])
{
	t_trace	ctx;

	if(geteuid() != 0)
		return (ft_traceroute_perm());

	if (argv[1] == NULL || ft_strequal(argv[1], "-h"))
		return (ft_traceroute_help());

	if (ft_traceroute_init(&ctx, argv[1]) == EXIT_FAILURE)
		ft_exit("traceroute_init()");

	ft_traceroute_exec(&ctx);
	// ft_traceroute_wait(&ctx);

	return (EXIT_SUCCESS);
}
