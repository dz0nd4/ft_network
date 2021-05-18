/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_network.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:10:56 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/10 21:55:31 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NETWORK_H
# define FT_NETWORK_H

# include "../ping/ft_ping.h"
# include "../traceroute/ft_traceroute.h"
# include "../nmap/ft_nmap.h"

typedef int			t_dist(int argc, const char *argv[]);

typedef enum		e_network_key
{
	FT_NET_PING,
	FT_NET_TRACEROUTE,
	FT_NET_NMAP,
	FT_NET_MAX
}					t_net_key;

typedef struct		s_network
{
	char		*name;
	t_dist	*dist;
}					t_net;

#endif
