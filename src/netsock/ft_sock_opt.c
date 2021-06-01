/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sock_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 18:18:12 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_netsock.h"

/*
 * ft_recvfrom
 *
 * Description:
 *    Abstraction over recvmsg function.
 * Returns:
 *    The number of data read or -1
*/
int   ft_setsockopt_ttl(int *fd, int ttl, int verbose)
{ 
  if (setsockopt(*fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) == 0)
    return (FT_EXOK);

  if (verbose)
		fprintf(stderr, "socket: Set TTL option failed.\n");

  return (FT_EXFAIL);
}

int   ft_setsockopt_sndtimeo(int *fd, int timeout, int verbose)
{ 
  t_timeval		tv;

	ft_memset(&tv, 0, sizeof(tv));
	tv.tv_sec = timeout;

  if (setsockopt(*fd, FT_SOL_SOCKET, SO_SNDTIMEO,
                  (const char*)&tv, sizeof(tv)) == 0)
    return (FT_EXOK);

  if (verbose)
		fprintf(stderr, "socket: Set SNDTIMEO option failed.\n");
  
  return (FT_EXFAIL);
}

int   ft_setsockopt_rcvtimeo(int *fd, int timeout, int verbose)
{ 
  t_timeval		tv;

	ft_memset(&tv, 0, sizeof(tv));
	tv.tv_sec = timeout;

  if (setsockopt(*fd, FT_SOL_SOCKET, SO_RCVTIMEO,
                  (const char*)&tv, sizeof(tv)) == 0)
    return (FT_EXOK);
  
  if (verbose)
			fprintf(stderr, "socket: Set RCVTIMEO option failed.\n");

  return (FT_EXFAIL);
}