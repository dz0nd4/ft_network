/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcap_compile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/20 14:07:38 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_sock.h"

/*
 * ft_pcap_compile_setfilter
 *
 * Description:
 *    Abstraction over recvmsg function.
 * Returns:
 *    The number of data read or -1
 */
int ft_pcap_compile_setfilter(pcap_t *handle, char *dev_addr, t_bpf dev_net,
                              int port) {
  char filter_exp[100];
  t_bpf_program fp = {0};

  // snprintf(filter_exp, 100, "((tcp) and (dst host %s))", dev_addr);
  snprintf(filter_exp, 100, "((dst host %s) and (src port %d))", dev_addr,
           port);

  /* Compile and apply the filter */
  if (pcap_compile(handle, &fp, filter_exp, 0, dev_net) == -1) {
    fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp,
            pcap_geterr(handle));
    return (FT_EXFAIL);
  }

  if (pcap_setfilter(handle, &fp) == -1) {
    fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp,
            pcap_geterr(handle));
    return (FT_EXFAIL);
  }

  pcap_freecode(&fp);
  return (FT_EXOK);
}