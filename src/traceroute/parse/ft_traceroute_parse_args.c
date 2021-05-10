/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_parse_args.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/10 12:00:23 by user42           ###   ########lyon.fr   */
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
int			ft_tr_arg_host(t_trace *ctx, char *arg)
{
	// t_addrinfo		hints;
	// t_addrinfo		*result;
	// t_addrinfo		*rp;

	// ft_memset(&hints, 0, sizeof(hints));
	// hints.ai_family = AF_INET;
	// hints.ai_socktype = SOCK_RAW;
	// hints.ai_protocol = IPPROTO_UDP;

	ctx->to.name = arg;
	// if (getaddrinfo(arg, NULL, &hints, &ctx->to.addrinfo) != 0)
	// 	return (ft_tr_error_host_resolve(ctx, arg));

	// rp = result;
	// while (rp != NULL) {
	// 	ctx->to.sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
	// 	if (ctx->to.sfd != INVALID_SOCKET)
	// 		break;
	// 	rp = rp->ai_next;
	// }

	// if (rp == NULL)
	// 	return (EXIT_FAILURE);

	// ft_memcpy(&ctx->to.saddrin, rp->ai_addr, sizeof(rp->ai_addr));
	// ft_memcpy(ctx->to.ip, inet_ntoa(ctx->to.saddrin.sin_addr), FT_ADDRSTRLEN);

	// free(result);

	// const int on = 1;

  // if (setsockopt (ctx->to.sfd, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof(on)) < 0)
	// 	return (EXIT_FAILURE);
  
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
int			ft_tr_arg_packetlen(t_trace *ctx, char *arg)
{
	int i;

	i = -1;
	while (arg[++i])
		if (!ft_isdigit(arg[i]))
			return (ft_tr_error_packetlen(ctx, "packetlen", arg));
	ctx->opts.packetlen = ft_atoi(arg);
	if (ctx->opts.packetlen > FT_PACKET_LEN_MAX) {
		fprintf(stderr, "too big packetlen %d specified\n", ctx->opts.packetlen);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}