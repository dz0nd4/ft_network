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

// int 	ft_tr_err_opt_bad(t_trace *ctx, const char *opt)
// {
// 	fprintf(stderr, "Bad option `%s` (argc %d)\n", opt, ctx->opts.argi);
// 	return (EXIT_FAILURE);
// }

int 	ft_tr_err_opt_require_arg(t_tr_args *args, const char *desc)
{
  const char *opt;

  opt = args->argv[args->argi];
	fprintf(stderr, "Option `%s` (argc %d) requires an argument: `%s %s`",
						opt, args->argi, opt, desc);
	return (EXIT_FAILURE);
}

int 	ft_tr_err_opt_handle(t_tr_args *args)
{
  const char *opt;
  const char *opt_arg;

  opt = args->argv[args->argi];
	opt_arg = args->argv[args->argi + 1];
  fprintf(stderr, "Cannot handle `%s' option with arg `%s' (argc %d)",
						opt, opt_arg, args->argi + 1);
	return (EXIT_FAILURE);
}

int 	ft_tr_err_arg_host(t_tr_args *args)
{
  const char *arg;

  arg = args->argv[args->argi];
	fprintf(stderr, "%s: Échec temporaire dans la résolution du nom\n", arg);
	fprintf(stderr, "Cannot handle \"host\" cmdline arg `%s' (argc %d)",
						arg, args->argi);
	return (EXIT_FAILURE);
}

int 	ft_tr_err_arg_packetlen(t_tr_args *args)
{
  const char *arg;

  arg = args->argv[args->argi];
	fprintf(stderr, "Cannot handle \"packetlen\" cmdline arg `%s' on position %d (argc %d)",
          arg, args->argi, args->argi);
	return (EXIT_FAILURE);
}


// int 	ft_tr_err_opt_out_range(t_trace *ctx, const char *opt, const char *arg)
// {
// 	fprintf(stderr, "Cannot handle `%s' option with arg `%s' (argc %d)",
// 						opt, arg, ctx->opts.argi);
// 	return (EXIT_FAILURE);
// }
