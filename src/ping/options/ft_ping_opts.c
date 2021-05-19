/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_opts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/19 21:18:07 by user42           ###   ########lyon.fr   */
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
 *   ft_ping_usage function
*/
int  ft_ping_opt_v(t_pg_opts *opts, t_pg_args *args)
{
  opts->verbose = 1;
  args->argi += 1;
  return (FT_EXOK);
}

/*
 * ft_ping_opt_s
 *
 * Description:
 *   -s: Specifies  the number of data bytes to be sent.
 * Returns:
 *   ft_ping_usage function
*/
int  ft_ping_opt_s(t_pg_opts *opts, t_pg_args *args)
{
  opts->packetsize = ft_atoi(args->argv[args->argi + 1]);
  args->argi += 2;
  return (FT_EXOK);
}
