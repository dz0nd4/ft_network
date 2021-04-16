/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/06 13:17:47 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
 * ft_tr_arg_f
 *
 * Description:
 *   -f: Start from the first_ttl hop (instead from 1)
 * Returns:
 *   EXIT_SUCCESS or EXIT_FAILURE if hops greater than hops_max
*/
int			ft_tr_arg_f(t_trace *ctx, char *arg)
{
	int i;

	i = -1;
	if (arg == NULL)
		return (ft_tr_error_arg(ctx, "-f", "first_ttl"));
	while (arg[++i])
		if (!ft_isdigit(arg[i]))
			return (ft_tr_error_arg_handle(ctx, "-f", arg));
	// ctx->args.hops = ft_atoi(arg);
	// if (ctx->args.hops > ctx->args.hops_max)
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
 * ft_tr_arg_m
 *
 * Description:
 *   -m: Set the max number of hops (max TTL to be reached). Default is 30
 * Returns:
 *   EXIT_SUCCESS
*/
int			ft_tr_arg_m(t_trace *ctx, char *arg)
{
	if (arg == NULL)
		return (ft_tr_error_arg(ctx, "-m", "max_ttl"));
	ctx->args.hops_max = ft_atoi(arg);
	return (EXIT_SUCCESS);
}

/*
 * ft_tr_arg_m
 *
 * Description:
 *   -q: Set the number of probes per each hop. Default is 3
 * Returns:
 *   EXIT_SUCCESS
*/
int			ft_tr_arg_q(t_trace *ctx, char *arg)
{
	if (arg == NULL)
		return (ft_tr_error_arg(ctx, "-q", "nqueries"));
	ctx->args.probes_max = ft_atoi(arg);
	return (EXIT_SUCCESS);
}

/*
 * ft_tr_arg_w
 *
 * Description:
 *   -w:
 * Returns:
 *   EXIT_SUCCESS
*/
int			ft_tr_arg_w(t_trace *ctx, char *arg)
{
	if (arg == NULL)
		return (ft_tr_error_arg(ctx, "-w", "MAX,HERE,NEAR"));
	return (EXIT_SUCCESS);
}

int			ft_traceroute_args(t_trace *ctx, int argc, const char *argv[])
{
	static t_tr_arg_d	ft_tr_arg[FT_TR_ARG_MAX] = {
		{ FT_TR_ARG_F, "f", ft_tr_arg_f },
		{ FT_TR_ARG_M, "m", ft_tr_arg_m },
		{ FT_TR_ARG_Q, "q", ft_tr_arg_q },
		{ FT_TR_ARG_W, "w", ft_tr_arg_w },
	};
	int							arg_key;
	char						*arg_name;

	arg_key = -1;
	arg_name = argv[ctx->argi] + 1;
	// if (arg_name == NULL)
	// 	return (EXIT_FAILURE);
	while (++arg_key < FT_TR_ARG_MAX)
		if (ft_strequ(ft_tr_arg[arg_key].arg_name, arg_name))
			return (ft_tr_arg[arg_key].arg_dist(ctx, argv[ctx->argi + 1]));
	return (ft_tr_error_bad_opt(ctx, arg_name));
}
