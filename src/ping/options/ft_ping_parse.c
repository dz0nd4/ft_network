/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 15:10:10 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

static int 	ft_pg_parse_init(t_pg_args *args, t_pg_opts	*opts)
{
	args->argi = 1;
	opts->ttl = FT_PING_DEFAULT_TTL;
	opts->packetsize = FT_PING_PACKETSIZE_DEFAULT;

	return (EXIT_SUCCESS);
}

static int		ft_pg_parse_opt(t_pg_opts *opts, t_pg_args *args)
{
	static t_ping_opt_d	ft_ping_opt[FT_PING_OPT_MAX] = {
		{ FT_PING_OPT_H, "h", ft_ping_opt_h },
		{ FT_PING_OPT_V, "v", ft_ping_opt_v },
		{ FT_PING_OPT_N, "n", ft_ping_opt_n },
		{ FT_PING_OPT_S, "s", ft_ping_opt_s },
		{ FT_PING_OPT_T, "t", ft_ping_opt_t },
	};
	int							opt_key;
	const char			*opt_name;

	opt_key = -1;
	opt_name = args->argv[args->argi] + 1;
	while (++opt_key < FT_PING_OPT_MAX)
		if (ft_strequ(ft_ping_opt[opt_key].opt_name, opt_name))
			return (ft_ping_opt[opt_key].opt_dist(opts, args));
	fprintf(stderr, "ft_ping: invalid option -- %s\n", opt_name);
	return (FT_EXFAIL);
}

/*
 * ft_ping_parse
 *
 * Description:
 *   Parse commandline
 * 	 If the argument begin with '-': it's option otherwise dest
 * Returns:
 *   FT_EXOK or FT_EXFAIL if ft_pg_parse_opt fails or dest is null
*/
int		ft_ping_parse(t_pg_opts *opts, int argc, const char *argv[])
{
	t_pg_args 	args;

	args.argc = argc;
	args.argv = argv;
	ft_pg_parse_init(&args, opts);

	while (args.argi < args.argc) {
		if (*argv[args.argi] == '-') {
			if (ft_pg_parse_opt(opts, &args) == FT_EXFAIL)
				return (FT_EXFAIL);
		} else {
			opts->dest = argv[args.argi];
			args.argi += 1;
		}
	}

	if (opts->dest == NULL)
		return (ft_ping_usage());

	return (FT_EXOK);
}