/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_parse_args.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 18:19:28 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

/*
 * ft_tr_arg_host
 *
 * Description:
 *    
 * Returns:
 *    EXIT_SUCCESS
*/
int			ft_tr_arg_host(t_trace *ctx, const char *arg)
{
	ctx->to.name = (char *)arg;
	ctx->to.addrinfo.ai_family = AF_INET;
	ctx->to.addrinfo.ai_socktype = SOCK_RAW;
	if (ft_sock_getaddrinfo(ctx->to.name, &ctx->to.addrinfo) == EXIT_FAILURE)
		return (ft_tr_error_host_resolve(ctx, arg));
	return (EXIT_SUCCESS);
}

/*
 * ft_tr_arg_packetlen
 *
 * Description:
 *    
 * Returns:
 *    EXIT_SUCCESS
*/
int			ft_tr_arg_packetlen(t_trace *ctx, const char *arg)
{
	int i;

	i = -1;
	if (!ft_isdigitstr(arg))
		return (ft_tr_error_packetlen(ctx, "packetlen", arg));
	ctx->opts.packetlen = ft_atoi(arg);
	if (ctx->opts.packetlen > FT_PACKET_LEN_MAX) {
		fprintf(stderr, "too big packetlen %d specified\n", ctx->opts.packetlen);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}