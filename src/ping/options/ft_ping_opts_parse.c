/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/18 17:06:47 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int 	ft_ping_opts_init(t_pg_opts	*opts)
{
	ft_memset(opts, 0, sizeof(t_pg_opts));

	opts->ttl = FT_PING_DEFAULT_TTL;
	opts->packetsize = FT_PING_DEFAULT_PACKETSIZE;
	return (EXIT_SUCCESS);
}


int		ft_ping_opts_parse(t_pg_opts *opts, const char *opt, const char *arg)
{
	static t_ping_opt_d	ft_ping_opt[FT_PING_OPT_MAX] = {
		{ FT_PING_OPT_H, "h", ft_ping_opt_h },
		{ FT_PING_OPT_V, "v", ft_ping_opt_v },
	};
	int							opt_key;
	char						*opt_name;

	opt_key = -1;
	opt_name = opt + 1;
	while (++opt_key < FT_PING_OPT_MAX)
		if (ft_strequ(ft_ping_opt[opt_key].opt_name, opt_name))
			return (ft_ping_opt[opt_key].opt_dist(opts, arg));
	return (ft_ping_exit(opt));
}
