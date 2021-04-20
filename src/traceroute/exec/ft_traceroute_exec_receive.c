/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_exec_receive.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/20 16:39:19 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

int   ft_traceroute_exec_receive(t_trace *ctx)
{
	fd_set fds;
	struct timeval wait;
	int waittime = 5;		/* time to wait for response (in seconds) */

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