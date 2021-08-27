/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_net.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/12 09:29:19 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_net.h"

static int ft_net_usage(const char *bin) {
  fprintf(stderr,
          "Usage:\n"
          "%s [ ping ] [ traceroute ] [ nmap ]\n"
          "Options:\n"
          "  ping         ping command: more help with -h\n"
          "  traceroute   traceroute command: more help with -h\n"
          "  nmap         nmap command: more help with -h\n\n",
          bin);
  return (FT_EXFAIL);
}

int main(int argc, const char *argv[]) {
  const t_net net_command[FT_NET_MAX] = {
      {"ping", ft_ping}, {"traceroute", ft_traceroute}, {"nmap", ft_nmap}};
  char *command = NULL;
  int key = -1;

  if ((command = (char *)argv[1]) == NULL) {
    return (ft_net_usage(argv[0]));
  }

  key = -1;
  while (++key < FT_NET_MAX)
    if (ft_strequ(command, net_command[key].name))
      return (net_command[key].dist(argc - 1, argv + 1));
  return (ft_net_usage(argv[0]));
}
