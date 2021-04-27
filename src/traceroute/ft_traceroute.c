/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/27 12:59:29 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int			ft_traceroute(int argc, const char *argv[])
{
	t_trace	ctx;

	ft_memset(&ctx, 0, sizeof(ctx));

	if (geteuid() != FT_TR_ROOT) {
		fprintf(stderr, "/!\\ You don't have root privileges /!\\\n");
		// return (EXIT_FAILURE);
	}

	if (argc < 2)
		return (ft_traceroute_usage((char *)argv[0]));

	if (ft_traceroute_parse(&ctx, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (ft_traceroute_execute(&ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
