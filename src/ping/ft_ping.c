/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/18 23:09:08 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_ping	g_ctx;

int			ft_ping(int argc, const char *argv[])
{
	int argi;
	t_pg_opts opts;

	argi = 1;
	// setuid(getuid());
	ft_ping_opts_init(&opts);
	while (argv[argi] && *argv[argi] == '-') {
		if (ft_ping_opts_parse(&opts, argv[argi], argv[argi + 1]) == FT_EXFAIL)
			return (FT_EXFAIL);
		argi += 1;
	}

	if (argv[argi] == NULL)
		return (ft_ping_usage());

	return (ft_ping_exec(argv[argi], opts));
}
