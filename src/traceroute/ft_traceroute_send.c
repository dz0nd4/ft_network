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

// void write_server(SOCKET sock, SOCKADDR_IN *sin, const char *buffer)
// {
//    if(sendto(sock, buffer, strlen(buffer), 0, (SOCKADDR *) sin, sizeof *sin) < 0)
//    {
//       perror("sendto()");
//       exit(errno);
//    } else {
// 		 printf("Send!\n");
// 	 }
// }

// static int read_server(SOCKET sock, SOCKADDR_IN *sin, char *buffer)
// {
//    int n = 0;
//    size_t sinsize = sizeof *sin;

// 	struct sockaddr_in source;

// 	memset(&source, 0, sizeof(source));

//    if((n = recvfrom(sock, buffer, BUF_SIZE - 1, 0, (SOCKADDR *) sin, &sinsize)) < 0)
//    {
//       perror("recvfrom()");
//       exit(errno);
//    }

//    buffer[n] = 0;

// 	struct ip *iph = (struct ip *)buffer;
// 	source.sin_addr.s_addr = iph->ip_dst.s_addr;
// 			char *str = inet_ntoa(sin->sin_addr);
// 			printf("%s\n", str);

//    return n;
// }
int waittime = 5;		/* time to wait for response (in seconds) */

int   ft_traceroute_receive(t_trace *ctx, int ttl)
{
	fd_set fds;
	struct timeval wait;

	FD_ZERO(&fds);
	FD_SET(ctx->sock_icmp, &fds);
	wait.tv_sec = waittime; wait.tv_usec = 0;

  char buffer[BUF_SIZE];
  int n = 0;

	t_sockaddr_in from;
  size_t from_size;
  
	memset(&from, 0, sizeof(from));
  from_size = sizeof(from);

	if (select(ctx->sock_icmp + 1, &fds, (fd_set *)0, (fd_set *)0, &wait) > 0)
    if((n = recvfrom(ctx->sock_icmp, buffer, BUF_SIZE - 1, 0, (t_sockaddr *)&from, &from_size)) < 0)
    {
      perror("recvfrom()");
      exit(errno);
    }

  // buffer[n] = 0;

	// struct ip *iph = (struct ip *)buffer;
	// source.sin_addr.s_addr = iph->ip_dst.s_addr;
  char *str = inet_ntoa(from.sin_addr);
  
  if (str) {
    printf(" %d (%s)\n", ttl, str);
  } else {
    printf(" %d *\n", ttl);
  }

  // return n;
  return (EXIT_SUCCESS);
}

int   ft_traceroute_send(t_trace *ctx, int port, int ttl)
{
  t_sockaddr_in to;
  t_socket      sfd;
  // char buffer[BUF_SIZE];

  // ft_memset(&to, 0, sizeof(ctx->to));
	// to.sin_family = AF_INET;
	// to.sin_addr.s_addr = inet_addr(ctx->host_ipv4);
	ctx->to.sin_port = htons(port);

  // if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	// 	ft_exit("socket()");

  if (setsockopt(ctx->sock_udp, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
		ft_exit("setsockopt()");

  if (sendto(ctx->sock_udp, NULL, 0, 0, (t_sockaddr *)&ctx->to, sizeof(t_sockaddr)) < 0)
		ft_exit("sendto()");

  return (EXIT_SUCCESS);
}