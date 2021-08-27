/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace_parse_opts.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 12:35:08 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
 * ft_tr_opt_err_req_arg
 *
 * Description:
 *   error function for missing arg
 * Returns:
 *   FT_EXFAIL
 */
static int ft_tr_opt_err_req_arg(t_arg *arg, const char *desc) {
  const char *opt;

  opt = arg->v[arg->i];
  fprintf(stderr, "Option `%s` (argc %d) requires an argument: `%s %s`", opt,
          arg->i, opt, desc);
  return (FT_EXFAIL);
}

/*
 * ft_tr_opt_err_handle_arg
 *
 * Description:
 *   error function for invalid arg
 * Returns:
 *   FT_EXFAIL
 */
static int ft_tr_opt_err_handle_arg(t_arg *arg) {
  const char *opt;
  const char *opt_arg;

  opt = arg->v[arg->i];
  opt_arg = arg->v[arg->i + 1];
  fprintf(stderr, "Cannot handle `%s' option with arg `%s' (argc %d)", opt,
          opt_arg, arg->i + 1);
  return (FT_EXFAIL);
}

/*
 * ft_tr_opt_f
 *
 * Description:
 *   -f: Start from the first_ttl hop (instead from 1)
 * Returns:
 *   FT_EXOK or FT_EXFAIL if hops greater than hops_max
 */
int ft_tr_opt_f(t_tr_opts *opts, t_arg *arg) {
  const char *opt_arg;

  opt_arg = arg->v[arg->i + 1];
  if (opt_arg == NULL) return (ft_tr_opt_err_req_arg(arg, "first_ttl"));
  if (!ft_isdigitstr(opt_arg)) return (ft_tr_opt_err_handle_arg(arg));
  opts->hops = ft_atoi(opt_arg);

  arg->i += 2;
  return (FT_EXOK);
}

/*
 * ft_tr_opt_m
 *
 * Description:
 *   -m: Set the max number of hops (max TTL to be reached). Default is 30
 * Returns:
 *   FT_EXOK
 */
int ft_tr_opt_m(t_tr_opts *opts, t_arg *arg) {
  const char *opt_arg;

  opt_arg = arg->v[arg->i + 1];
  if (opt_arg == NULL) return (ft_tr_opt_err_req_arg(arg, "max_ttl"));
  if (!ft_isdigitstr(opt_arg)) return (ft_tr_opt_err_handle_arg(arg));
  opts->hops_max = ft_atoi(opt_arg);

  if (opts->hops_max > FT_HOPS_MAX) {
    fprintf(stderr, "max hops cannot be more than %d\n", FT_HOPS_MAX);
    return (FT_EXFAIL);
  }

  arg->i += 2;
  return (FT_EXOK);
}

/*
 * ft_tr_opt_q
 *
 * Description:
 *   -q: Set the number of probes per each hop. Default is 3
 * Returns:
 *   FT_EXOK
 */
int ft_tr_opt_q(t_tr_opts *opts, t_arg *arg) {
  const char *opt_arg;

  opt_arg = arg->v[arg->i + 1];
  if (opt_arg == NULL) return (ft_tr_opt_err_req_arg(arg, "nqueries"));
  if (!ft_isdigitstr(opt_arg)) return (ft_tr_opt_err_handle_arg(arg));
  opts->probes_max = ft_atoi(opt_arg);
  if (opts->probes_max < 1 || opts->probes_max > FT_PROBES_MAX) {
    fprintf(stderr, "no more than %d probes per hop\n", FT_PROBES_MAX);
    return (FT_EXFAIL);
  }
  return (FT_EXOK);
}

/*
 * ft_tr_opt_h
 *
 * Description:
 *   -h:
 * Returns:
 *   FT_EXOK
 */
int ft_tr_opt_h(t_tr_opts *opts, t_arg *arg) { return (ft_traceroute_usage()); }