/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_errors_args.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/23 12:40:39 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int 	ft_tr_error_host()
{
	fprintf(stderr, "Specify \"host\" missing argument.\n");
	return (EXIT_FAILURE);
}

int 	ft_tr_error_host_resolve(t_trace *ctx, char *arg)
{
	fprintf(stderr, "%s: Échec temporaire dans la résolution du nom\n", arg);
	fprintf(stderr, "Cannot handle \"host\" cmdline arg `%s' (argc %d)",
						arg, ctx->argi);
	return (EXIT_FAILURE);
}

int 	ft_tr_error_packetlen(t_trace *ctx, char *opt, char *arg)
{
	fprintf(stderr, "Cannot handle \"packetlen\" cmdline arg `q' on position 2 (argc 2)");
	return (EXIT_FAILURE);
}
