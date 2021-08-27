/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcap_lookup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/07/26 20:45:45 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_sock.h"

/*
 * ft_pcap_lookupdev
 *
 * Description:
 *    Abstraction over recvmsg function.
 * Returns:
 *    The number of data read or -1
 */
int ft_pcap_lookupdev(char **dev) {
  char errbuf[PCAP_ERRBUF_SIZE]; /* Error string */

  /* Define the device */
  *dev = pcap_lookupdev(errbuf);
  if (*dev == NULL) {
    fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
    return (FT_EXFAIL);
  }
  return (FT_EXOK);
}

/*
 * ft_pcap_lookupnet
 *
 * Description:
 *    Abstraction over recvmsg function.
 * Returns:
 *    The number of data read or -1
 */
int ft_pcap_lookupnet(char *dev, bpf_u_int32 *net, bpf_u_int32 *mask) {
  char errbuf[PCAP_ERRBUF_SIZE]; /* Error string */

  /* Find the properties for the device */
  if (pcap_lookupnet((const char *)dev, net, mask, errbuf) == -1) {
    fprintf(stderr, "Couldn't get netmask for device %s: %s\n", dev, errbuf);
    *net = 0;
    *mask = 0;
  }
  return (FT_EXOK);
}
