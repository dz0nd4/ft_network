/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_opts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/20 12:56:58 by user42           ###   ########lyon.fr   */
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
int  ft_ping_opt_h(t_pg_opts *opts, t_pg_args *args)
{
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
int  ft_ping_opt_v(t_pg_opts *opts, t_pg_args *args)
{
  opts->verbose = 1;
  args->argi += 1;
  return (FT_EXOK);
}

/*
 * ft_ping_opt_n
 *
 * Description:
 *   -n: Numeric output only.  No attempt will be made to lookup symbolic names for host addresses.
 * Returns:
 *   FT_EXOK
*/
int  ft_ping_opt_n(t_pg_opts *opts, t_pg_args *args)
{
  opts->numeric_only = 1;
  args->argi += 1;
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
int  ft_ping_opt_s(t_pg_opts *opts, t_pg_args *args)
{
  opts->packetsize = ft_atoi(args->argv[args->argi + 1]);
  args->argi += 2;
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
int  ft_ping_opt_t(t_pg_opts *opts, t_pg_args *args)
{
  if (!ft_isdigitstr(args->argv[args->argi + 1]))
    return (ft_ping_error_opt_ttl());
  opts->ttl = ft_atoi(args->argv[args->argi + 1]);
  args->argi += 2;
  return (FT_EXOK);
}
