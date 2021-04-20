/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/20 15:47:20 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

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
			return (ft_tr_error_arg_handle(ctx, "packetlen", arg));
	ctx->opts.packetlen = ft_atoi(arg);
	if (ctx->opts.packetlen > FT_PACKET_LEN_MAX) {
		fprintf(stderr, "too big packetlen %d specified\n", ctx->opts.packetlen);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}