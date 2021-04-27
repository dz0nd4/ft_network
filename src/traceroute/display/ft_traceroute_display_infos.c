/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_display_infos.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/26 12:04:36 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int   ft_traceroute_display_infos_host(t_trace *ctx)
{
	printf("traceroute to %s (%s), %d hops max, %d byte packets\n",
		ctx->host.name, ctx->host.ip, ctx->opts.hops_max, ctx->opts.packetlen);
  return (EXIT_SUCCESS);
}
