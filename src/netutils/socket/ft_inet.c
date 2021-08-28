/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/27 17:00:58 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_socket.h"

/*
 * ft_inet_ntop
 *
 * Description:
 *    Abstraction over inet_ntop function.
 * 		It assumes 'ip' length is FT_ADDRSTRLEN
 * 		NUMERIC to PRINTABLE
 * Returns:
 *    FT_EXOK or FT_EXFAIL if inet_ntop fail
 */
int ft_inet_ntop(t_in_addr *src, char *dst) {
  if (inet_ntop(AF_INET, src, dst, FT_ADDRSTRLEN) == NULL) {
    fprintf(stderr, "inet_ntop\n");
    return (FT_EXFAIL);
  }
  return (FT_EXOK);
}

int ft_inet_pton(t_in_addr *addr, char *ipv4) {
  int domain;
  int s;

  domain = AF_INET;
  s = inet_pton(domain, ipv4, addr);
  if (s <= 0) return (FT_EXFAIL);
  return (FT_EXOK);
}

int ft_inet_ntoa(t_in_addr *src, char *dst) {
  if ((dst = inet_ntoa(*src)) == NULL) return (FT_EXFAIL);
  return (FT_EXOK);
}
