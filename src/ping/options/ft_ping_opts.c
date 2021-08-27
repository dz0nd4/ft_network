/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_opts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/07/26 18:51:56 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

/*
 * ft_ping_opt_h
 *
 * Description:
 *   -h: Show help.
 * Returns:
 *   ft_ping_usage function
 */
int ft_ping_opt_h(t_pg_opts *opts, t_arg *arg) {
  (void)opts;
  (void)arg;
  return (ft_ping_usage());
}

/*
 * ft_ping_opt_v
 *
 * Description:
 *   -v: Verbose output.
 * Returns:
 *   FT_EXOK
 */
int ft_ping_opt_v(t_pg_opts *opts, t_arg *arg) {
  opts->verbose = 1;
  arg->i += 1;
  return (FT_EXOK);
}

/*
 * ft_ping_opt_n
 *
 * Description:
 *   -n: Numeric output only.  No attempt will be made to lookup symbolic names
 * for host addresses. Returns: FT_EXOK
 */
int ft_ping_opt_n(t_pg_opts *opts, t_arg *arg) {
  opts->numeric_only = 1;
  arg->i += 1;
  return (FT_EXOK);
}

/*
 * ft_ping_opt_s
 *
 * Description:
 *   -s: Specifies  the number of data bytes to be sent.
 * Returns:
 *   FT_EXOK
 */
int ft_ping_opt_s(t_pg_opts *opts, t_arg *arg) {
  const char argv = arg->v[arg->i + 1];
  unsigned int argvi = 0;

  if (!ft_isdigitstr(argv)) {
    fprintf(stderr, "ft_ping: can't set packet size: Argument invalide\n");
    return (FT_EXFAIL);
  }

  argvi = (unsigned int)ft_atoi(argv);
  if (argvi > (FT_UINT16_MAX - FT_PING_HDR)) {
    fprintf(stderr, "ft_ping packet size %u is too large. Maximum is %d\n",
            argvi, FT_UINT16_MAX - FT_PING_HDR);
    return (FT_EXFAIL);
  }

  opts->packetsize = ft_atoi(arg->v[arg->i + 1]);
  arg->i += 2;
  return (FT_EXOK);
}

/*
 * ft_ping_opt_t
 *
 * Description:
 *   -t: ttl ping only.  Set the IP Time to Live.
 * Returns:
 *   FT_EXOK
 */
int ft_ping_opt_t(t_pg_opts *opts, t_arg *arg) {
  const char argv = arg->v[arg->i + 1];
  int argvi = 0;

  if (!ft_isdigitstr(argv)) {
    fprintf(stderr,
            "ft_ping: can't set unicast time-to-live: Argument invalide\n");
    return (FT_EXFAIL);
  }

  argvi = (unsigned int)ft_atoi(argv);
  if (argvi > FT_UINT8_MAX) {
    fprintf(stderr, "ft_ping: ttl %d out of range\n", argvi);
    return (FT_EXFAIL);
  }

  opts->ttl = argvi & FT_UINT8_MAX;

  arg->i += 2;
  return (FT_EXOK);
}
