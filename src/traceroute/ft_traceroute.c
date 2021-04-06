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

static int read_server(SOCKET sock, SOCKADDR_IN *sin, char *buffer)
{
   int n = 0;
   size_t sinsize = sizeof *sin;

	struct sockaddr_in source;

	memset(&source, 0, sizeof(source));

   if((n = recvfrom(sock, buffer, BUF_SIZE - 1, 0, (SOCKADDR *) sin, &sinsize)) < 0)
   {
      perror("recvfrom()");
      exit(errno);
   }

   buffer[n] = 0;

	struct ip *iph = (struct ip *)buffer;
	source.sin_addr.s_addr = iph->ip_dst.s_addr;
			char *str = inet_ntoa(sin->sin_addr);
			printf("%s\n", str);

   return n;
}

static void write_server(SOCKET sock, SOCKADDR_IN *sin, const char *buffer)
{
   if(sendto(sock, buffer, strlen(buffer), 0, (SOCKADDR *) sin, sizeof *sin) < 0)
   {
      perror("sendto()");
      exit(errno);
   } else {
		 printf("Send!\n");
	 }
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

	printf("traceroute to %s (%s), %d hops, %d byte packets\n", ctx->target_ipv4, ctx->target_ipv4, ctx->hops, ctx->byte_packets);

	for (int i = 1; i < 30; i++) {

		ft_traceroute_send(ctx, port + i, i);
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

	// printf("ft_traceroute \n");
	if (ft_traceroute_init(&ctx, argv[1]) == EXIT_FAILURE) {
		ft_exit("traceroute_init()");
	}

	ft_traceroute_exec(&ctx);
	// ft_traceroute_wait(&ctx);

	return (EXIT_SUCCESS);
}
