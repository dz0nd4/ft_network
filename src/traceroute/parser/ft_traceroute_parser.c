/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_parser.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/20 16:11:23 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static int	ft_tr_opt_dispatch(t_trace *ctx, int argc, const char *argv[])
{
	static t_tr_opt_d	ft_tr_opt[FT_TR_OPT_MAX] = {
		{ FT_TR_OPT_F, "f", ft_tr_opt_f },
		{ FT_TR_OPT_M, "m", ft_tr_opt_m },
		{ FT_TR_OPT_Q, "q", ft_tr_opt_q },
		{ FT_TR_OPT_W, "w", ft_tr_opt_w },
	};
	int							opt_key;
	char						*opt_name;

	opt_key = -1;
	opt_name = argv[ctx->argi] + 1;
	while (++opt_key < FT_TR_OPT_MAX)
		if (ft_strequ(ft_tr_opt[opt_key].opt_name, opt_name))
			return (ft_tr_opt[opt_key].opt_dist(ctx, argv[ctx->argi + 1]));
	return (ft_tr_error_bad_opt(ctx, opt_name));
}

int			ft_traceroute_parse(t_trace *ctx, int argc, const char *argv[])
{
	ctx->argi = 1;

	// ft_tr_init_args(ctx);

	// if (argv[ctx->argi] == NULL)
	// 	return (ft_traceroute_help((char *)argv[0]));

	while (argv[ctx->argi] && *argv[ctx->argi] == '-') {
		if (ft_tr_opt_dispatch(ctx, argc, argv) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		ctx->argi += 2;
	}

	if (argv[ctx->argi] == NULL)
		return (ft_tr_error_host());

	ctx->host.name = argv[ctx->argi++];

	if (argv[ctx->argi] != NULL) {
		ft_tr_arg_packetlen(ctx, argv[ctx->argi]);
	}

	return (EXIT_SUCCESS);
}

int			ft_traceroute_parse_debug(t_trace *ctx)
{
	printf("|------------------|\n");
	printf("host: %s\n", ctx->host.name);

	printf("hops: %d\n", ctx->opts.hops);
	printf("hops_max: %d\n", ctx->opts.hops_max);
	printf("probes_max: %d\n", ctx->opts.probes_max);
	printf("packetlen: %d\n", ctx->opts.packetlen);
	printf("|------------------|\n");
	return (EXIT_SUCCESS);
}
