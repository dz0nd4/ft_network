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
 *   FT_EXOK or FT_EXFAIL if hops greater than hops_max
*/
int			ft_tr_opt_f(t_trace *ctx, t_tr_args *args)
{
	const char *opt_arg;

	opt_arg = args->argv[args->argi + 1];
	if (opt_arg == NULL)
		return (ft_tr_err_opt_require_arg(args, "first_ttl"));
	if (!ft_isdigitstr(opt_arg))
		return (ft_tr_err_opt_handle(args));
	ctx->opts.hops = ft_atoi(opt_arg);
	// if (ctx->opts.hops > ctx->opts.hops_max) {
	// 	fprintf(stderr, "first hop out of range\n");
	// 	return (FT_EXFAIL);
	// }

	args->argi += 2;
	return (FT_EXOK);
}

/*
 * ft_tr_opt_m
 *
 * Description:
 *   -m: Set the max number of hops (max TTL to be reached). Default is 30
 * Returns:
 *   FT_EXOK
*/
int			ft_tr_opt_m(t_trace *ctx, t_tr_args *args)
{
	const char *opt_arg;

	opt_arg = args->argv[args->argi + 1];
	if (opt_arg == NULL)
		return (ft_tr_err_opt_require_arg(args, "max_ttl"));
	if (!ft_isdigitstr(opt_arg))
		return (ft_tr_err_opt_handle(args));
	ctx->opts.hops_max = ft_atoi(opt_arg);
	// if (ctx->opts.hops > ctx->opts.hops_max) {
	// 	fprintf(stderr, "first hop out of range\n");
	// 	return (FT_EXFAIL);
	// }

	if (ctx->opts.hops_max > FT_HOPS_MAX) {
		fprintf(stderr, "max hops cannot be more than %d\n", FT_HOPS_MAX);
		return (FT_EXFAIL);
	}

	args->argi += 2;
	return (FT_EXOK);
}

/*
 * ft_tr_opt_q
 *
 * Description:
 *   -q: Set the number of probes per each hop. Default is 3
 * Returns:
 *   FT_EXOK
*/
int			ft_tr_opt_q(t_trace *ctx, t_tr_args *args)
{
	const char *opt_arg;

	opt_arg = args->argv[args->argi + 1];
	if (opt_arg == NULL)
		return (ft_tr_err_opt_require_arg(args, "nqueries"));
	if (!ft_isdigitstr(opt_arg))
		return (ft_tr_err_opt_handle(args));
	ctx->opts.probes_max = ft_atoi(opt_arg);
	if (ctx->opts.probes_max < 1 || ctx->opts.probes_max > FT_PROBES_MAX) {
		fprintf(stderr, "no more than %d probes per hop\n", FT_PROBES_MAX);
		return (FT_EXFAIL);
	}
	return (FT_EXOK);
}

/*
 * ft_tr_opt_w
 *
 * Description:
 *   -w:
 * Returns:
 *   FT_EXOK
*/
int			ft_tr_opt_w(t_trace *ctx, t_tr_args *args)
{
	if (args == NULL)
		return (ft_tr_err_opt_require_arg(args, "MAX,HERE,NEAR"));
	return (FT_EXOK);
}

/*
 * ft_tr_opt_h
 *
 * Description:
 *   -h:
 * Returns:
 *   FT_EXOK
*/
int			ft_tr_opt_h(t_trace *ctx, t_tr_args *args)
{
	return (FT_EXOK);
}