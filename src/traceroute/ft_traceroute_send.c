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

int   ft_traceroute_send(t_trace *ctx, int port, int ttl)
{
  t_sockaddr_in to;
  t_socket      sfd;
  // char buffer[BUF_SIZE];

  ft_memset(&to, 0, sizeof(to));
	to.sin_family = AF_INET;
	to.sin_addr.s_addr = inet_addr(ctx->host_ipv4);
	to.sin_port = htons(port);

  if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
		ft_exit("socket()");

  if (setsockopt(sfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
		ft_exit("setsockopt()");

  if (sendto(sfd, NULL, 0, 0, (t_sockaddr *)&to, sizeof(t_sockaddr)) < 0)
		ft_exit("sendto()");

  return (EXIT_SUCCESS);
}