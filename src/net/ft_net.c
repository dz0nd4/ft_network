/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_net.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/19 15:20:44 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_net.h"

int			main(int argc, const char *argv[])
{
  static const t_net net_command[FT_NET_MAX] = {
    { "./ft_ping", ft_ping },
    { "./ft_traceroute", ft_traceroute },
    { "./ft_nmap", ft_nmap }
  };
  int key;

  key = -1;
  // while (++key < FT_NET_MAX)
  //   if (ft_strequal(argv[0], net_command[key].name))
  //     return (net_command[key].dist(argc, argv));
	return (ft_ping(argc, argv));
}
