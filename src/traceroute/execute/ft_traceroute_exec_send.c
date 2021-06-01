/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_execute_send.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 15:02:40 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

/*
 * ft_traceroute_execute_send
 *
 * Description:
 *    Send probe with custom TTL
 * Returns:
 *    The number data send
*/
int   ft_traceroute_exec_send(t_tr_opts *opts, t_tr_to *to)
{
  t_ip *ip;
  t_udp *udp;
	int i;

	ip = (t_ip *)to->data;
	udp = (t_udp *)&to->data[FT_IPHDR_LEN];

	ip->ip_ttl = opts->hops;
  udp->uh_dport = htons(opts->port + opts->hops + opts->probes); 

	ft_sock_gettime(&to->time.start);

	i = ft_sock_send(to->sfd, to->data, opts->packetlen, &to->saddrin);

  return (i);
}
