/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_parse_opts.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 12:35:08 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
 * ft_tr_opt_f
 *
 * Description:
 *   -f: Start from the first_ttl hop (instead from 1)
 * Returns:
 *   EXIT_SUCCESS or EXIT_FAILURE if hops greater than hops_max
*/
int			ft_tr_opt_f(t_trace *ctx, const char *arg)
{
	int i;

	i = -1;
	if (arg == NULL)
		return (ft_trace_error_opt_arg_require(ctx, "-f", "first_ttl"));
	if (!ft_isdigitstr(arg))
		return (ft_trace_error_opt_arg_handle(ctx, "-f", arg));
	ctx->opts.hops = ft_atoi(arg);
	if (ctx->opts.hops > ctx->opts.hops_max) {
		fprintf(stderr, "first hop out of range\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
 * ft_tr_opt_m
 *
 * Description:
 *   -m: Set the max number of hops (max TTL to be reached). Default is 30
 * Returns:
 *   EXIT_SUCCESS
*/
int			ft_tr_opt_m(t_trace *ctx, const char *arg)
{
	int i;

	i = -1;
	if (arg == NULL)
		return (ft_trace_error_opt_arg_require(ctx, "-m", "max_ttl"));
	while (arg[++i])
		if (!ft_isdigit(arg[i]))
			return (ft_trace_error_opt_arg_handle(ctx, "-m", arg));
	ctx->opts.hops_max = ft_atoi(arg);
	if (ctx->opts.hops > ctx->opts.hops_max) {
		fprintf(stderr, "first hop out of range\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
 * ft_tr_opt_q
 *
 * Description:
 *   -q: Set the number of probes per each hop. Default is 3
 * Returns:
 *   EXIT_SUCCESS
*/
int			ft_tr_opt_q(t_trace *ctx, const char *arg)
{
	int i;

	i = -1;
	if (arg == NULL)
		return (ft_trace_error_opt_arg_require(ctx, "-q", "nqueries"));
	while (arg[++i])
		if (!ft_isdigit(arg[i]))
			return (ft_trace_error_opt_arg_handle(ctx, "-q", arg));
	ctx->opts.probes_max = ft_atoi(arg);
	if (ctx->opts.probes_max < 1 || ctx->opts.probes_max > 10) {
		fprintf(stderr, "no more than 10 probes per hop\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
 * ft_tr_opt_w
 *
 * Description:
 *   -w:
 * Returns:
 *   EXIT_SUCCESS
*/
int			ft_tr_opt_w(t_trace *ctx, const char *arg)
{
	if (arg == NULL)
		return (ft_trace_error_opt_arg_require(ctx, "-w", "MAX,HERE,NEAR"));
	return (EXIT_SUCCESS);
}

/*
 * ft_tr_opt_h
 *
 * Description:
 *   -h:
 * Returns:
 *   EXIT_SUCCESS
*/
int			ft_tr_opt_h(t_trace *ctx, const char *arg)
{
	return (EXIT_SUCCESS);
}