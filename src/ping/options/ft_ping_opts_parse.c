/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_opts_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 23:39:41 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int 	ft_ping_opts_init(int argc, const char *argv[], t_pg_args *args, t_pg_opts	*opts)
{
	ft_memset(args, 0, sizeof(t_pg_args));
	ft_memset(opts, 0, sizeof(t_pg_opts));

	args->argc = argc;
	args->argv = argv;
	args->argi = 1;

	opts->ttl = FT_PING_DEFAULT_TTL;
	opts->packetsize = FT_PING_PACKETSIZE_DEFAULT;

	return (EXIT_SUCCESS);
}

int		ft_ping_opts_parse(t_pg_opts *opts, t_pg_args *args)
{
	static t_ping_opt_d	ft_ping_opt[FT_PING_OPT_MAX] = {
		{ FT_PING_OPT_H, "h", ft_ping_opt_h },
		{ FT_PING_OPT_V, "v", ft_ping_opt_v },
		{ FT_PING_OPT_N, "n", ft_ping_opt_n },
		{ FT_PING_OPT_S, "s", ft_ping_opt_s },
		{ FT_PING_OPT_T, "t", ft_ping_opt_t },
	};
	int							opt_key;
	char						*opt_name;

	opt_key = -1;
	opt_name = args->argv[args->argi] + 1;
	while (++opt_key < FT_PING_OPT_MAX)
		if (ft_strequ(ft_ping_opt[opt_key].opt_name, opt_name))
			return (ft_ping_opt[opt_key].opt_dist(opts, args));
	fprintf(stderr, "ft_ping: invalid option -- %s\n", opt_name);
	return (FT_EXFAIL);
}
