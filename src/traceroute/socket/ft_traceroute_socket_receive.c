/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_socket_receive.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/26 11:47:05 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

int   ft_traceroute_socket_receive_init(t_trace *ctx)
{
  if ((ctx->sock.icmp = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == INVALID_SOCKET)
		return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int   ft_traceroute_socket_receive(t_trace *ctx)
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

  char type;
  char code;

  t_ip *ip = (t_ip *)buffer;
  // printf("%d\n", ip->ip_hl << 2);
  int hlen = ip->ip_hl << 2;

  struct icmp *icmp = (t_icmp *)(buffer + hlen);

	type = icmp->icmp_type; code = icmp->icmp_code;

  // if (code == ICMP_UNREACH)
  //   printf("DEST UNREACH\n");

  ip = &icmp->icmp_ip;



  hlen = ip->ip_hl << 2;

  t_udp *udp = (t_udp *)((u_char *)ip + hlen);

  // if (ip->ip_id == getpid()) {
  //       printf("valid packet\n");
  // } else {
  //   printf("invalid packet");
  // }

  // if (udp->uh_sport == htons(getpid())) {
  //   printf("valid packet\n");
  // } else {
  //   printf("invalid packet");
  // }

  return (n);
}