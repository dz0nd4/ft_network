/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_socket_receive.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/27 16:57:29 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

int   ft_traceroute_socket_receive_init(t_trace *ctx)
{
  if ((ctx->from.sfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == INVALID_SOCKET)
		return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int   ft_traceroute_socket_receive(t_trace *ctx, char *buffer)
{
  const int waittime = 5;
	fd_set    fds;
	t_timeval wait;
  int from_size;
  int cc;

	FD_ZERO(&fds);
	FD_SET(ctx->from.sfd, &fds);

  wait.tv_sec = waittime;
  wait.tv_usec = 0;
  
  from_size = sizeof(ctx->from.saddrin);

	if (select(ctx->from.sfd + 1, &fds, (fd_set *)0, (fd_set *)0, &wait) > 0)
    if((cc = recvfrom(ctx->from.sfd, buffer, BUF_SIZE - 1, 0, (t_sockaddr *)&ctx->from.saddrin, &from_size)) < 0)
    {
      perror("recvfrom()");
      exit(errno);
    }

  return (cc);
}
