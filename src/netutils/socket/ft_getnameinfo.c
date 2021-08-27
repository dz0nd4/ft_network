/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnameinfo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/07/28 13:48:00 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_sock.h"

/*
 * ft_getnameinfo
 *
 * Description:
 *    Abstraction over ft_getnameinfo function.
 * 		It assumes dst is FT_NI_MAXHOST length
 * Returns:
 *    The number of data read or -1
 */
int ft_getnameinfo(t_sockaddr_in *host, char *name) {
  socklen_t len;
  char hbuf[FT_NI_MAXHOST];

  len = sizeof(t_sockaddr_in);

  if (getnameinfo((t_sockaddr *)host, len, hbuf, FT_NI_MAXHOST, NULL, 0,
                  FT_NI_NAMEREQD)) {
    if (ft_inet_ntop((t_in_addr *)&host->sin_addr, hbuf) == FT_EXFAIL)
      return (FT_EXFAIL);
    ft_strcpy(name, hbuf);
  } else {
    ft_strcpy(name, hbuf);
  }

  return (FT_EXOK);
}

/*
 * ft_getnameinfo
 *
 * Description:
 *    Abstraction over ft_getnameinfo function.
 * 		It assumes dst is FT_NI_MAXHOST length
 * Returns:
 *    The number of data read or -1
 */
char *ft_getnameinfo_pr(t_sockaddr_in *host, char *hostname) {
  if (ft_getnameinfo(host, hostname) == FT_EXFAIL) return (NULL);

  return (hostname);
}

/*
 * ft_getnameinfo
 *
 * Description:
 *    Abstraction over ft_getnameinfo function.
 * 		It assumes dst is FT_NI_MAXHOST length
 * Returns:
 *    The number of data read or -1
 */
int ft_getnameinfo_err(const char *bin, const char *hostname) {
  fprintf(stderr, "%s: cannot resolve %s: Unknown host\n", bin, hostname);
  return (FT_EXFAIL);
}