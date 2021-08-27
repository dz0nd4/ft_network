/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getifaddr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/07/28 13:59:00 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_sock.h"

/*
 * ft_getifaddrs
 *
 * Description:
 *    Abstraction over ft_getnameinfo function.
 * 		It assumes dst is FT_NI_MAXHOST length
 * Returns:
 *    The number of data read or -1
 */
int ft_getifaddrs(t_ifaddrs **ifaddrs) {
  if (getifaddrs(ifaddrs) == -1) {
    perror("getifaddrs");
    return (FT_EXFAIL);
  }
  return (FT_EXOK);
}

/*
 * ft_getifaddr
 *
 * Description:
 *    Abstraction over ft_getnameinfo function.
 * 		It assumes dst is FT_NI_MAXHOST length
 * Returns:
 *    The number of data read or -1
 */
int ft_getifaddr(const char *dev_name, char **dev_addr) {
  t_ifaddrs *ifaddrs;
  t_sockaddr_in *in;
  int family;

  if (ft_getifaddrs(&ifaddrs)) return (FT_EXFAIL);

  /* Walk through linked list, maintaining head pointer so we
   can free list later. */
  for (t_ifaddrs *ifa = ifaddrs; ifa != NULL; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr == NULL) continue;

    in = (t_sockaddr_in *)ifa->ifa_addr;
    family = ifa->ifa_addr->sa_family;

    if (family == AF_INET && ft_strequ(dev_name, (const char *)ifa->ifa_name)) {
      // printf("ifa_name: %s\n", ifa->ifa_name);
      *dev_addr = inet_ntoa(in->sin_addr);
      freeifaddrs(ifaddrs);
      return (FT_EXOK);
    }
  }

  freeifaddrs(ifaddrs);

  return (FT_EXFAIL);
};
