/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_errors_opts.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 12:37:00 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int 	ft_trace_error_opt_bad(t_trace *ctx, const char *opt)
{
	fprintf(stderr, "Bad option `%s` (argc %d)\n", opt, ctx->opts.argi);
	return (EXIT_FAILURE);
}

int 	ft_trace_error_opt_arg_require(t_trace *ctx, const char *opt, const char *arg)
{
	fprintf(stderr, "Option `%s` (argc %d) requires an argument: `%s %s`",
						opt, ctx->opts.argi, opt, arg);
	return (EXIT_FAILURE);
}

int 	ft_trace_error_opt_arg_handle(t_trace *ctx, const char *opt, const char *arg)
{
	fprintf(stderr, "Cannot handle `%s' option with arg `%s' (argc %d)",
						opt, arg, ctx->opts.argi);
	return (EXIT_FAILURE);
}

int 	ft_trace_error_opt_out_range(t_trace *ctx, const char *opt, const char *arg)
{
	fprintf(stderr, "Cannot handle `%s' option with arg `%s' (argc %d)",
						opt, arg, ctx->opts.argi);
	return (EXIT_FAILURE);
}
