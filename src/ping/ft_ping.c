/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/20 18:59:14 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_ping	g_ctx;
t_pg	g_pg = { 0 };

static void ft_ping_init_args(t_pg_args *args, int argc, const char *argv[])
{
	ft_memset(args, 0, sizeof(t_pg_args));
	args->argc = argc;
	args->argv = argv;
	args->argi = 1;
}

int			ft_ping(int argc, const char *argv[])
{
	t_pg_args args;
	t_pg_opts *opts = &g_pg.opts;

	setuid(getuid());
	ft_ping_init_args(&args, argc, argv);
	ft_ping_opts_init(opts);
	while (argv[args.argi] && *argv[args.argi] == '-') {
		if (ft_ping_opts_parse(opts, &args) == FT_EXFAIL)
			return (FT_EXFAIL);
	}

	if (argv[args.argi] == NULL)
		return (ft_ping_usage());

	// return 1;
	return (ft_ping_exec(argv[args.argi], *opts));
}
