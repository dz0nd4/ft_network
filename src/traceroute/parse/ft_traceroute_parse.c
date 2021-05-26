/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 12:33:29 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static int	ft_traceroute_parse_init(t_trace *ctx)
{
	ctx->opts.argi = 1;
	ctx->opts.hops = FT_DEFAULT_HOPS;
	ctx->opts.hops_max = FT_DEFAULT_HOPS_MAX;
	ctx->opts.probes_max = FT_DEFAULT_PROBES_MAX;
	ctx->opts.port = FT_DEFAULT_PORT;
	ctx->opts.packetlen = sizeof(t_ip) + 40;
	return (EXIT_SUCCESS);
}

static int	ft_traceroute_parse_opt(t_trace *ctx, int argc, const char *argv[])
{
	static t_tr_opt_d	ft_tr_opt[FT_TR_OPT_MAX] = {
		{ FT_TR_OPT_F, "f", ft_tr_opt_f },
		{ FT_TR_OPT_M, "m", ft_tr_opt_m },
		{ FT_TR_OPT_Q, "q", ft_tr_opt_q },
		{ FT_TR_OPT_W, "w", ft_tr_opt_w },
	};
	int							opt_key;
	const char			*opt_name;

	opt_key = -1;
	opt_name = argv[ctx->opts.argi] + 1;
	while (++opt_key < FT_TR_OPT_MAX)
		if (ft_strequ(ft_tr_opt[opt_key].opt_name, opt_name))
			return (ft_tr_opt[opt_key].opt_dist(ctx, argv[ctx->opts.argi + 1]));
	return (ft_trace_error_opt_bad(ctx, opt_name));
}

int			ft_traceroute_parse(t_trace *ctx, int argc, const char *argv[])
{
	ft_traceroute_parse_init(ctx);

	while (argv[ctx->opts.argi] && *argv[ctx->opts.argi] == '-') {
		if (ft_traceroute_parse_opt(ctx, argc, argv) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		ctx->opts.argi += 2;
	}

	if (argv[ctx->opts.argi] == NULL)
		return (ft_tr_error_host());

	if (ft_tr_arg_host(ctx, argv[ctx->opts.argi++]) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (argv[ctx->opts.argi] != NULL)
		ft_tr_arg_packetlen(ctx, argv[ctx->opts.argi]);

	return (EXIT_SUCCESS);
}
