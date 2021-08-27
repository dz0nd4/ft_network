/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace_execute_recv.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/27 01:00:48 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

int ft_trace_exec_recv_print_flag(int code) {
  static t_sock_icmp_type icmp[5] = {
      {ICMP_NET_UNREACH, " !N"},  {ICMP_HOST_UNREACH, " !H"},
      {ICMP_PROT_UNREACH, " !P"}, {ICMP_FRAG_NEEDED, " !F"},
      {ICMP_SR_FAILED, " !S"},
  };
  int i;

  i = -1;
  while (++i < 5)
    if (code == icmp[i].type_int) {
      printf("%s", icmp[i].type_str);
      return (FT_EXOK);
    }
  return (FT_EXFAIL);
}

int ft_trace_exec_pckt(t_tr_opts *opts, t_tr_sock *to, t_tr_sock *from) {
  static char host_name[FT_NI_MAXHOST];
  char *host_addr;

  // register t_icmp *icp = (t_icmp *)&from->data[FT_IPHDR_LEN];
  // t_ip *ip = &icp->icmp_ip;
  t_icmphdr *icp = (t_icmphdr *)&from->data[FT_IPHDR_LEN];
  t_iphdr *ip = (t_iphdr *)&icp->un.echo.id;
  t_udphdr *udp = (t_udphdr *)((t_uchar *)ip + FT_IPHDR_LEN);

  // printf("udpport %d\n", udp->uh_dport);

  t_timeval *timeval = (t_timeval *)(&from->data[FT_PING_HDR + FT_TRACE_HDR]);

  double elapsed_time = 0;

  if (timeval->tv_sec || timeval->tv_usec)
    elapsed_time = ft_getelapsedtime(timeval);

  // printf("recv: ");
  // printf("%d %0.2f ms \n", from->cc, elapsed_time);
  // hexdump(&from->data[FT_PING_HDR + FT_TRACE_HDR], FT_TIMEVAL_LEN);
  // printf("\n");

  t_icmphdr *icmp = (t_icmphdr *)&from->data[FT_IPHDR_LEN];
  t_uchar type, code;

  type = icmp->type;
  code = icmp->code;

  if ((type == ICMP_TIME_EXCEEDED && code == ICMP_EXC_TTL) ||
      type == ICMP_DEST_UNREACH) {
    char tmp[FT_NI_MAXHOST];
    ft_getnameinfo(&from->saddrin, tmp);

    if (!ft_strequ(host_name, tmp)) {
      ft_memcpy(host_name, tmp, FT_NI_MAXHOST);
      printf("%s (%s)  ", host_name, inet_ntoa(from->saddrin.sin_addr));
    }

    printf(" %0.2f ms ", elapsed_time);

    if (type != ICMP_TIME_EXCEEDED) ft_trace_exec_recv_print_flag(code);

    if (type == ICMP_DEST_UNREACH && opts->probes + 1 == opts->probes_max) {
      printf("\n");
      return (FT_EXOK);
    }
  }
  return (FT_EXFAIL);
}

int ft_trace_exec_recv(t_tr_opts *opts, t_tr_sock *to, t_tr_sock *from) {
  fd_set fds;

  FD_ZERO(&fds);

  FD_SET(from->fd, &fds);

  if (select(from->fd + 1, &fds, (fd_set *)0, (fd_set *)0, &from->tv)) {
    if ((from->cc =
             ft_recvfrom(from->fd, from->data, from->datalen, &from->saddrin)))
      return (ft_trace_exec_pckt(opts, to, from));
  }

  printf(" *");
  fflush(stdout);

  return (FT_EXFAIL);
}
