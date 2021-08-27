/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace_execute_init.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/27 00:55:01 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int ft_trace_exec_init(t_tr_opts *opts, t_tr_sock *to, t_tr_sock *from) {}

int ft_trace_exec_init_to(t_tr_opts *opts, t_tr_sock *to) {
  t_addrinfo addrinfo;

  ft_memset(&addrinfo, 0, sizeof(0));

  addrinfo.ai_family = AF_INET;
  addrinfo.ai_socktype = SOCK_DGRAM;
  addrinfo.ai_protocol = IPPROTO_UDP;

  if (ft_getaddrinfo(opts->host, &addrinfo) == FT_EXFAIL) {
    fprintf(stderr, "Unkown host\n");
    return (FT_EXFAIL);
  }

  if ((to->fd = ft_socket_raw()) == INVALID_SOCKET) return (FT_EXFAIL);

  ft_memcpy(&to->saddrin, addrinfo.ai_addr, sizeof(addrinfo.ai_addr));

  to->datalen = opts->packetlen;
  if ((to->data = ft_memalloc(opts->packetlen)) == NULL) return (EXIT_FAILURE);

  ft_sock_pckt_udphdr(to->data, to->datalen, to->saddrin, opts->port);

  return (FT_EXOK);
}

int ft_trace_exec_init_from(t_tr_opts *opts, t_tr_sock *from) {
  const int waittime = 2;

  // ft_memset(from, 0, sizeof(t_tr_from));

  if ((from->fd = ft_socket_icmp()) == INVALID_SOCKET) return (FT_EXFAIL);
  // ft_setsockopt_rcvtimeo(&from->sfd, 1, 1);

  from->datalen = 250;
  if ((from->data = ft_memalloc(opts->packetlen)) == NULL) return (FT_EXFAIL);

  // from->saddrin_size = sizeof(from->saddrin);
  from->tv.tv_sec = waittime;
  from->tv.tv_usec = 0;

  return (FT_EXOK);
}
