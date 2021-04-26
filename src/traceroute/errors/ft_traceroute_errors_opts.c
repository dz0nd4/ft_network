/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_errors_opts.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/23 12:41:25 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int 	ft_tr_error_bad_opt(t_trace *ctx, char *opt)
{
	fprintf(stderr, "Bad option `%s` (argc %d)\n", opt, ctx->argi);
	return (EXIT_FAILURE);
}

int 	ft_tr_error_arg(t_trace *ctx, char *opt, char *arg)
{
	fprintf(stderr, "Option `%s` (argc %d) requires an argument: `%s %s`",
						opt, ctx->argi, opt, arg);
	return (EXIT_FAILURE);
}

int 	ft_tr_error_arg_handle(t_trace *ctx, char *opt, char *arg)
{
	fprintf(stderr, "Cannot handle `%s' option with arg `%s' (argc %d)",
						opt, arg, ctx->argi);
	return (EXIT_FAILURE);
}
