/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:14:00 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/27 17:07:41 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOOLS_H
# define FT_TOOLS_H

#include <sys/time.h>

#include "../../ft_net_global.h"

#define FT_TIMEVAL_LEN sizeof(struct timeval)

typedef struct timeval t_timeval;

/*
 *  TOOLS TIME
 */
int ft_gettimeofday(t_timeval *tv);
int ft_delay();
double ft_timediff(t_timeval *out, t_timeval *in);
double ft_getelapsedtime(t_timeval *in);

#endif
