/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_net.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:10:56 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/19 15:20:52 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NET_H
# define FT_NET_H

# include "../ping/ft_ping.h"
# include "../traceroute/ft_traceroute.h"
# include "../nmap/ft_nmap.h"

typedef int			t_dist(int argc, const char *argv[]);

typedef enum		e_net_key
{
	FT_NET_PING,
	FT_NET_TRACEROUTE,
	FT_NET_NMAP,
	FT_NET_MAX
}					t_net_key;

typedef struct		s_net
{
	char		*name;
	t_dist	*dist;
}					t_net;

#endif
