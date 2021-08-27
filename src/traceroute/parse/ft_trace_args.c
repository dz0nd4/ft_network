/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace_parse_args->c                         :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/27 00:52:10 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

/*
 * ft_tr_arg_err_pcktlen
 *
 * Description:
 *   error function for error on packet len
 * Returns:
 *   FT_EXFAIL
 */
static int ft_tr_arg_err_pcktlen(t_arg *arg) {
  const char *pcktlen;

  pcktlen = arg->v[arg->i];
  fprintf(
      stderr,
      "Cannot handle \"packetlen\" cmdline arg `%s' on position %d (argc %d)",
      pcktlen, arg->i, arg->i);
  return (EXIT_FAILURE);
}

/*
 * ft_tr_arg_host
 *
 * Description:
 *
 * Returns:
 *    FT_EXOK
 */
int ft_tr_arg_host(t_tr_opts *opts, t_arg *arg) {
  // const char *arg;
  t_addrinfo addrinfo;

  // arg = arg->v[args->argi];
  opts->host = arg->v[arg->i];
  // ctx->to.name = (char *)arg;
  // addrinfo.ai_family = AF_INET;
  // addrinfo.ai_socktype = SOCK_DGRAM;
  // addrinfo.ai_protocol = IPPROTO_UDP;
  // if (ft_getaddrinfo(ctx->to.name, &ctx->to.addrinfo) == FT_EXFAIL)
  // 	return (ft_tr_err_arg_host(args));
  return (FT_EXOK);
}

/*
 * ft_tr_arg_packetlen
 *
 * Description:
 *
 * Returns:
 *    FT_EXOK
 */
int ft_tr_arg_packetlen(t_tr_opts *opts, t_arg *arg) {
  const char *pcktlen;

  pcktlen = arg->v[arg->i];
  if (!ft_isdigitstr(pcktlen)) return (ft_tr_arg_err_pcktlen(arg));
  opts->packetlen = ft_atoi(pcktlen);
  if (opts->packetlen < 0 || opts->packetlen > FT_PACKETLEN_MAX) {
    fprintf(stderr, "too big packetlen %d specified\n", opts->packetlen);
    return (FT_EXFAIL);
  }
  if (opts->packetlen < 28) opts->packetlen = 28;
  return (FT_EXOK);
}