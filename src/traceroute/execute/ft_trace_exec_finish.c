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

int ft_trace_exec_finish_to(t_tr_sock *to) {
  close(to->fd);
  free(to->data);

  return (FT_EXOK);
}

int ft_trace_exec_finish_from(t_tr_opts *opts, t_tr_sock *from) {
  t_icmphdr *icmp = (t_icmphdr *)&from->data[FT_IPHDR_LEN];
  t_uchar type, code;

  type = icmp->type;
  code = icmp->code;
  close(from->fd);
  free(from->data);

  if (code == ICMP_DEST_UNREACH && opts->probes == opts->probes_max)
    return (FT_EXOK);
  return (FT_EXFAIL);
}
