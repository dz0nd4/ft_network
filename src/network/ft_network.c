/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_network.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/03/23 19:08:33 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_network.h"

int			main(int argc, const char *argv[])
{
  static const t_net net_command[FT_NET_MAX] = {
    { "./ft_traceroute", ft_traceroute },
    { "./ft_nmap", ft_nmap }
  };
  int key;

  key = -1;
  while (++key < FT_NET_MAX)
    if (ft_strequal(argv[0], net_command[key].name))
      return (net_command[key].dist(argc, argv));
	return (EXIT_FAILURE);
}
