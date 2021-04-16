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

int waittime = 5;		/* time to wait for response (in seconds) */

int   ft_traceroute_receive(t_trace *ctx)
{
	fd_set fds;
	struct timeval wait;

	FD_ZERO(&fds);
	FD_SET(ctx->sock.icmp, &fds);
	wait.tv_sec = waittime; wait.tv_usec = 0;

  char buffer[BUF_SIZE];
  int n = 0;

	// t_sockaddr_in from;
  int from_size;
  
	// memset(&from, 0, sizeof(from));
  from_size = sizeof(ctx->from);

	if (select(ctx->sock.icmp + 1, &fds, (fd_set *)0, (fd_set *)0, &wait) > 0)
    if((n = recvfrom(ctx->sock.icmp, buffer, BUF_SIZE - 1, 0, (t_sockaddr *)&ctx->from, &from_size)) < 0)
    {
      perror("recvfrom()");
      exit(errno);
    }

  return (n);
}

int   ft_traceroute_send(t_trace *ctx)
{
  t_sockaddr_in to;
  struct timeval tv;
  char buffer[32];
  int port = 33435;

  ft_bzero(buffer, 32);
  ft_strcpy(buffer, "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_");
  // char buffer[BUF_SIZE];

  ft_memset(&to, 0, sizeof(to));
	to.sin_family = AF_INET;
  to.sin_port = htons(port + ctx->args.hops + ctx->args.probes);
	to.sin_addr.s_addr = inet_addr(ctx->host.ip);

  gettimeofday(&ctx->tv, NULL);

  if (setsockopt(ctx->sock.udp, IPPROTO_IP, IP_TTL,
        &ctx->args.hops, sizeof(ctx->args.hops)) < 0)
		ft_exit("setsockopt()");

  if (sendto(ctx->sock.udp, buffer, sizeof(buffer), 0, (t_sockaddr *)&to, sizeof(t_sockaddr)) < 0)
		ft_exit("sendto()");

  return (EXIT_SUCCESS);
}