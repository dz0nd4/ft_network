/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_parse_args->c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/27 00:52:10 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

/*
 * ft_tr_arg_host
 *
 * Description:
 *    
 * Returns:
 *    FT_EXOK
*/
int			ft_tr_arg_host(t_trace *ctx, t_tr_args *args)
{
	// const char *arg;
	t_addrinfo	addrinfo;

	// arg = args->argv[args->argi];
	ctx->opts.host = args->argv[args->argi];
	// ctx->to.name = (char *)arg;
	// addrinfo.ai_family = AF_INET;
	// addrinfo.ai_socktype = SOCK_DGRAM;
	// addrinfo.ai_protocol = IPPROTO_UDP;
	// if (ft_getaddrinfo(ctx->to.name, &ctx->to.addrinfo) == FT_EXFAIL)
	// 	return (ft_tr_err_arg_host(args));
	return (FT_EXOK);
}

/*
 * ft_tr_arg_packetlen
 *
 * Description:
 *    
 * Returns:
 *    FT_EXOK
*/
int			ft_tr_arg_packetlen(t_trace *ctx, t_tr_args *args)
{
	const char *arg;

	arg = args->argv[args->argi];
	if (!ft_isdigitstr(arg))
		return (ft_tr_err_arg_packetlen(args));
	ctx->opts.packetlen = ft_atoi(arg);
	if (ctx->opts.packetlen < 0 || ctx->opts.packetlen > FT_PACKETLEN_MAX) {
		fprintf(stderr, "too big packetlen %d specified\n", ctx->opts.packetlen);
		return (FT_EXFAIL);
	}
	return (FT_EXOK);
}