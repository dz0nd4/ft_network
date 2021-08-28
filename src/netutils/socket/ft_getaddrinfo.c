/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getaddrinfo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/27 17:01:03 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_socket.h"

/*
 * ft_getaddrinfo
 *
 * Description:
 *    Abstraction over ft_getaddrinfo function
 * Returns:
 *    The number of data read or -1
 */
int ft_getaddrinfo(const char *host, t_addrinfo *host_addrinfo) {
  t_addrinfo hints = {0};
  t_addrinfo *result = NULL;
  t_addrinfo *rp = NULL;
  int fd = INVALID_SOCKET;

  // ft_memset(&hints, 0, sizeof(hints));
  hints.ai_family = host_addrinfo->ai_family;
  hints.ai_socktype = host_addrinfo->ai_socktype;
  hints.ai_protocol = host_addrinfo->ai_protocol;
  hints.ai_flags = FT_AI_CANONNAME;

  if (getaddrinfo(host, NULL, (struct addrinfo *)&hints,
                  (struct addrinfo **)&result) != 0)
    return (FT_EXFAIL);

  rp = result;
  while (rp != NULL) {
    fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (fd != INVALID_SOCKET) break;
    rp = rp->ai_next;
  }
  if (rp == NULL) return (FT_EXFAIL);

  *host_addrinfo = *rp;
  // ft_memcpy(host_addrinfo, rp, sizeof(t_addrinfo));

  close(fd);
  freeaddrinfo((struct addrinfo *)result);

  return (FT_EXOK);
}
