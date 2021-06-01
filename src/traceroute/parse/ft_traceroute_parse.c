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

static int	ft_traceroute_parse_init(t_trace *ctx, t_tr_args *args)
{
	args->argi = 1;

	ctx->opts.argi = 1;
	ctx->opts.hops = FT_HOPS_FIRST_DEFAULT;
	ctx->opts.hops_max = FT_HOPS_MAX_DEFAULT;
	ctx->opts.probes_max = FT_PROBES_DEFAULT;
	ctx->opts.port = FT_PORT_DEFAULT;
	ctx->opts.packetlen = sizeof(t_ip) + 40;
	return (FT_EXOK);
}

static int	ft_traceroute_parse_opt(t_trace *ctx, t_tr_args *args)
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
	opt_name = args->argv[args->argi] + 1;
	while (++opt_key < FT_TR_OPT_MAX)
		if (ft_strequ(ft_tr_opt[opt_key].opt_name, opt_name))
			return (ft_tr_opt[opt_key].opt_dist(ctx, args));
	fprintf(stderr, "Bad option `%s` (argc %d)\n", opt_name, args->argi);
	return (FT_EXFAIL);
}

int			ft_traceroute_parse(t_trace *ctx, int argc, const char *argv[])
{
	t_tr_args args;

	args.argc = argc;
	args.argv = argv;
	ft_traceroute_parse_init(ctx, &args);

	while (args.argi < args.argc) {
		if (*argv[args.argi] == '-') {
			if (ft_traceroute_parse_opt(ctx, &args) == FT_EXFAIL)
				return (FT_EXFAIL);
		} else {
			if (ctx->opts.host == NULL)
				ft_tr_arg_host(ctx, &args);
				// ctx->opts.dest = argv[args.argi];
			else if (ctx->opts.packetlen == FT_PACKETLEN_DEFAULT)
				ft_tr_arg_packetlen(ctx, &args);
				// ctx->opts.packetlen = arg
			args.argi += 1;
		}
		// ctx->opts.argi += 2;
	}

	if (ctx->opts.host == NULL) {
		fprintf(stderr, "Specify \"host\" missing argument.\n");
		return (FT_EXFAIL);
	}

	if (ctx->opts.hops > ctx->opts.hops_max) {
		fprintf(stderr, "first hop out of range\n");
		return (FT_EXFAIL);
	}

	// if (ft_tr_arg_host(ctx, argv[args.argi]) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);

	// if (argv[ctx->opts.argi] != NULL)
	// 	ft_tr_arg_packetlen(ctx, argv[args.argi]);

	return (FT_EXOK);
}
