/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_execute_send.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/10 15:14:43 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

/*
 * ft_traceroute_execute_send
 *
 * Description:
 *    Send probe with custom TTL
 * Returns:
 *    0 if the target is reached or max hops is reached
 *    1 otherwise
*/
int   ft_traceroute_execute_send(t_trace *ctx, t_tr_opt *opts, t_tr_to *to)
{
	opts->probes++;
 
 	if (ctx->from.code == ICMP_UNREACH && opts->probes >= opts->probes_max)
    return (0);

	if (opts->probes >= opts->probes_max) {
		opts->probes = 0;
		opts->hops++;
	}
  if (opts->hops > opts->hops_max)
		return (0);

	to->hdr->ip.ip_ttl = opts->hops;
  to->hdr->udp.uh_dport = htons(opts->port + opts->hops + opts->probes); 
  gettimeofday(&ctx->time.start, NULL);

	if (ft_socket_send(to->sfd, to->pack.data, opts->packetlen, &to->saddrin) == EXIT_FAILURE)
		return (0);

  return (1);
}
