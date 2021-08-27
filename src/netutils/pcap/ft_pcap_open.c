/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcap_open.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/14 13:56:03 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_sock.h"

/*
 * ft_pcap_open_live
 *
 * Description:
 *    Abstraction over pcap_open_live function.
 * Returns:
 *    The number of data read or -1
 */
int ft_pcap_open_live(pcap_t **handle, char *dev_name) {
  char errbuf[PCAP_ERRBUF_SIZE]; /* Error string */

  /* Open the session in promiscuous mode */
  *handle = pcap_open_live(dev_name, BUFSIZ, 1, 1000, errbuf);
  if (*handle == NULL) {
    fprintf(stderr, "Couldn't open device %s: %s\n", dev_name, errbuf);
    return (FT_EXFAIL);
  }
  return (FT_EXOK);
}
